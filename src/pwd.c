#include  "minishell.h"

int	pwd(void *arg, char **envp)
{
	char cwd[PATH_MAX];

	(void) arg;
	(void) envp;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("Unable to get filesystem path for current directory");
		return (-1);
	}
	write(STDIN_FILENO, cwd, ft_strlen(cwd));
	write(STDIN_FILENO, "\n", 1);
	return (0);
}
