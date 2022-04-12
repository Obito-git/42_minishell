#include "minishell.h"

int	child_status(int wstatus)
{
	int status;

	status = wstatus;
	if (WIFEXITED(wstatus))
		status = WIFEXITED(wstatus);
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(wstatus);
	return (status);
}

