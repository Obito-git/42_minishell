#include "minishell.h"

int	xport(void *a, t_strlist *env)
{
	char **args;
	int i;
	int y;

	args = (char **) a;
	i = 0;
	while (args[i])
	{
		y = 0;
		if (args[i][1] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
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
