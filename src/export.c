#include "minishell.h"

int	xport(t_command *cmd, t_strlist *env)
{
	char	**args;
	int		i;
	int		y;

	args = cmd->args;
	i = 0;
	while (args[i])
	{
		y = 0;
		if (args[i][1] == '=')
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
	return (update_strlist_envp(env));
}
