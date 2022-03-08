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
int	command1_child(int pid1, t_command *c)
{
	if (pid1 < 0)
		return (0);
	if (pid1 == 0)
	{
		dup2(c->tube[1], STDOUT_FILENO);
		dup2(c->infile_fd, STDIN_FILENO);
		close(c->tube[0]);
		close(c->tube[1]);
		execve(c->cmd1, c->cmd1_args, NULL);
	}
	return (1);
}

int	pipex(t_command *c)
{
	int	pid;

	pid = fork();
	if (!command1_child(pid1, c))
		return (0);
	pid2 = fork();
	if (!command2_child(pid2, c))
		return (0);
	close(c->tube[0]);
	close(c->tube[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (1);
} */