#include "minishell.h"

int	unset(t_command *cmd, t_strlist *env)
{
	char		**arg;
	t_strlist	var_list;
	size_t		len;

	arg = cmd->args;
	while (*arg)
	{
		var_list = *env;
		len = ft_strlen(*arg);
		while (var_list.size--)
		{

			if (ft_strncmp(var_list.head->str, *arg, len) == 0)
			{
				remove_node_from_strlist(env, var_list.head);
				break;
			}
			var_list.head = var_list.head->next;
		}
		arg++;
	}
	return (update_strlist_envp(env));
}
