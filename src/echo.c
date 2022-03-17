#include "minishell.h"

//Can't print variables yet !
int	echo(void *a, char **envp)
{
	char **args;
	bool newline;

	newline = true;
	args = (char**) ++a;
	if (!ft_strcmp(*args, "-n"))
	{
		newline = false;
		args++;
	}
	if (*args)
	{
		write(STDIN_FILENO, *args, ft_strlen(*args));
		args++;
	}
	while (*args)
	{
		printf(" %s", *args);
		args++;
	}
	if (newline)
		printf("\n");
	return (0);
}
