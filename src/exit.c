#include "minishell.h"

int	xit(t_command *cmd, t_strlist *env)
{

	ft_dprintf_str(STDERR_FILENO, "exit\n");
	free_commands(cmd);
	free_strlist(env);
	exit(0);
}
