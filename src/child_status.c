#include "minishell.h"

int	child_status(int wstatus)
{
	int	status;

	status = wstatus;
	if (WIFEXITED(wstatus))
		status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		status = 128 + WTERMSIG(wstatus);
	return (status);
}

