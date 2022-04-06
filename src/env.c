#include "minishell.h"

int	env(t_command *cmd, t_strlist *env)
{
	t_strlist	var_list;

	(void) cmd;
	var_list = *env;
	while (var_list.size--)
	{
		printf("%s\n", var_list.head->str);
		var_list.head = var_list.head->next;
	}
	return (0);
}
