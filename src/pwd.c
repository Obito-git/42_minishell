#include  "minishell.h"

int	pwd(t_command *cmd, t_strlist *env)
{
	char	cwd[PATH_MAX];
	char	*res;

	(void) cmd;
	(void) env;
	getcwd(cwd, sizeof(cwd));
	res = cwd;
	if (!res)
	{
		perror("Unable to get filesystem path for current directory");
		return (-1);
	}
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
