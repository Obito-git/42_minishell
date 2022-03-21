#include "minishell.h"

int	xit(t_command *cmd, t_strlist *env)
{

	printf("exit\n");
	free_commands(cmd);
	free_strlist(env);
	exit(0);
}
