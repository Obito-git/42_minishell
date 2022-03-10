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
		if (!test_path || access(test_path, X_OK) == 0)
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


void	exec_com(int pid, t_command *c, char **envp)
{
	char	*path;
	int		out_fd;
	int		in_fd;

	path = NULL;
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		path = find_command(envp, c);
		if (!path && (!c->prev || !c->prev->out_mode))
		{
			printf("Unknown command %s\n", c->command);
			return ;
		}
		out_fd = set_out_path(c);
		set_tubes_path(c);
		if (path && (!c->prev || !c->prev->out_mode))
			execve(path, c->args, NULL);
		if (out_fd != -1)
			close(out_fd);
	}
	free(path);
	(void) in_fd;
}

void	execute(t_command *c, char **envp)
{
	t_command	*tmp;
	int			pid;

	pid = -1;
	tmp = c;
	while (pid != 0 && tmp)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork: ");
			return ;
		}
		exec_com(pid, tmp, envp);
		tmp = tmp->next;
	}
	close(c->tube[0]);
	close(c->tube[1]);
	while (wait(NULL) != -1 || errno != ECHILD)
		;
	if (pid == 0)
	{
		free_commands(c);
		exit(0);
	}

	//	waitpid(c->pid, NULL, 0); //err prot
}