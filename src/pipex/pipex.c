#include "../../minishell.h"

char	*find_command(char **envp, t_command *c)
{
	char	**splited;
	int		i;
	char	*test_path;

	i = 0;
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	splited = ft_split(*envp, ':');
	while (splited && splited[i++])
	{
		test_path = ft_strjointri(splited[i], "/", c->command);
		if (access(test_path, X_OK) == 0)
			break ;
		free(test_path);
		test_path = NULL;
	}
	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	free(splited);
	return (test_path);
}
/*
* tube[0] → contiendra le fichier descripteur de l'extrémité de lecture
* tube[1] → contiendra le fichier descripteur de l'extrémité d'écriture
*/
int	set_tube_path(t_command *c)
{
	int	fd;

	fd = -1;
	if (c->out_mode)
	{
		if (c->out_mode == OUT_APPEND)
			fd = open(c->next->command, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (c->out_mode == OUT_REWRITE)
			fd = open(c->next->command, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(c->next->command);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
	}
	return (fd);
}

int	exec_com(t_command *c, char **envp)
{
	char	*path;
	int		fd;

	path = NULL;
	if (c->pid < 0)
		return (0);
	if (c->pid == 0)
	{
		path = find_command(envp, c);
		if (!path)
		{
			printf("Unknown command %s\n", c->command);
			return (0);
		}
		fd = set_tube_path(c);
		execve(path, c->args, NULL);
		close(fd);
	}
	free(path);
	return (1);
}

t_bool	execute(t_command *c, char **envp)
{
	c->pid = fork();
	if (c->pid == -1)
	{
		perror("Fork: ");
		return (FALSE);
	}
	if (!exec_com(c, envp))
		return (FALSE);
	waitpid(c->pid, NULL, 0);
	return (1);
}