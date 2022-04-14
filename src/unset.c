#include "minishell.h"

static bool valid_var_id(char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (false);
	str++;
	while (*str)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

static void	remove_var_from_stem(char *stem, t_strlist *env)
{
	t_strlist	var_list;
	size_t		stem_len;

	var_list = *env;
	stem_len = ft_strlen(stem);
	while (var_list.size--)
	{
		if (ft_strncmp(var_list.head->str, stem, stem_len) == 0)
		{
			remove_node_from_strlist(env, var_list.head);
			break ;
		}
		var_list.head = var_list.head->next;
	}
}

int	unset(t_command *cmd, t_strlist *env)
{
	char		**arg;

	arg = cmd->args;
	while (*arg)
	{
		if (valid_var_id(*arg))
			remove_var_from_stem(*arg, env);
		else
			ft_dprintf_str(2, "%s: unset: `%s': not a valid identifier\n",
					HEADER, *arg);
		arg++;
	}
	return (update_strlist_strarr_value(env));
}
