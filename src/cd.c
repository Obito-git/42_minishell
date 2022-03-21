#include "minishell.h"

int	cd(t_command *cmd, t_strlist *env)
{
	char **	paths;
	int 	ret;

	(void) env;
	paths = cmd->args;
	paths++;
	if (paths[0])
	{
		if (paths[1])
		{
			printf("minishell: cd: too many arguments\n");
			return (1);
		}
		else
		{
			ret = chdir(paths[0]);
			if (ret)
				printf("minishell: cd: %s: No such file or directory\n",
						paths[0]);
			return (0);
		}
	}
	else
			printf("minishell: cd: you must provide a path\n");
	return (1);
}
