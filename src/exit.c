#include "minishell.h"

int	xit(t_command *cmd, t_strlist *env)
{
	size_t	args_count;
	int		ret;

	args_count = 0;
	while (cmd->args && cmd->args[args_count])
		args_count++;
	if (args_count > 2)
	{
		ft_dprintf_str(STDERR_FILENO, "%sexit: too many arguments\n", HEADER);
		env->ret = 1;
		return (env->ret);
	}
	else if (args_count <= 1)
		ret = 0;
	else
		ret = ft_atoi(cmd->args[1]);
	ft_dprintf_str(STDERR_FILENO, "exit\n");
	free_commands(cmd);
	free_strlist(env);
	exit(ret);
}
