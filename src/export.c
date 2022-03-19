#include "minishell.h"

int	_export(void *a, t_strlist *env)
{
	char **args;
	int i;
	int y;

	args = (char **) a;
	i = 0;
	while (args[i])
	{
		y = 0;
		while (args[i][y])
		{
			if (args[i][y] == '=')
				append_str_to_strlist(env, args[i]);
			y++;
		}
		i++;
	}
	return (0);
}
