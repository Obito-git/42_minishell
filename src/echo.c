#include "minishell.h"

int	echo(void *a, char **envp)
{
	char	**args;
	bool	newline;

	(void) envp;
	newline = true;
	args = (char **)a;
	args++;
	if (!ft_strncmp(*args, "-n", ft_strlen(*args)))
	{
		newline = false;
		args++;
	}
	while (*args)
	{
		write(STDIN_FILENO, *args, ft_strlen(*args));
		if (*(args + 1))
			write(STDIN_FILENO, " ", 1);
		args++;
	}
	if (newline)
		write(STDIN_FILENO, "\n", 1);
	return (0);
}
