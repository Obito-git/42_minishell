#include "minishell.h"

int	unset(void *args, t_strlist *env)
{
	char		**arg;
	t_strlist	var_list;
	size_t		len;

	arg = (char **) args;
	var_list = *env;
	while (*arg)
	{
		len = ft_strlen(*arg);
		while (var_list.size--)
		{

			if (ft_strncmp(var_list.head->str, *arg, len) == 0
					&& *(var_list.head->str + len) == '=')
				remove_node_from_strlist(env, var_list.head);
			var_list.head = var_list.head->next;
		}
		arg++;
	}
	return (0);
}
