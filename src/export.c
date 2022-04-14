#include "minishell.h"

static bool invalid_var_id(char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (true);
	str++;
	while (*str && *str != '=')
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (true);
		str++;
	}
	return (false);
}

int	xport(t_command *cmd, t_strlist *env)
{
	char	**args;
	int		i;
	int		y;

	args = cmd->args;
	i = 0;
	args++;
	/*for (int i =0; args[i]; i++)*/
	/*{*/
	/*    printf("%s\n", args[i]);*/
	/*}*/
	while (args[i])
	{
		y = 0;
		if (invalid_var_id(args[i]))
		{
			ft_dprintf_str(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n",
				args[i]);
			return (1);
		}
		while (args[i][y])
		{
			if (args[i][y] == '=')
				append_str_to_strlist(env, args[i]);
			y++;
		}
		i++;
	}
	return (update_strlist_strarr_value(env));
}
