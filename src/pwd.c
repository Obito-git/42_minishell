#include  "minishell.h"

int	pwd(t_command *cmd, t_strlist *env)
{
	char cwd[PATH_MAX];

	(void) cmd;
	(void) env;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("Unable to get filesystem path for current directory");
		return (-1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
