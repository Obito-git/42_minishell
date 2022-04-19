/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:02:21 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:02:21 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errors(char *arg, long ret)
{
	bool	sign;

	sign = false;
	if (ret < 0)
		sign = true;
	if (ret == 0 && (!isnumeric_str(&arg[sign])
			|| ft_strlen(&arg[sign]) > 19
			|| ((ft_strlen(arg) == 20
					&& ft_strcmp("-9223372036854775808", arg) < 0))
			|| (ft_strlen(arg) == 19
				&& ft_strcmp("9223372036854775807", arg) < 0)))
	{
		ft_dprintf_str(2, HEADER "exit: %s: numeric argument required\n", arg);
		return (2);
	}
	if (ret < 0 && ret >= -256)
		ret -= 256;
	return (ret % 256);
}

int	xit(t_command *cmd, t_strlist *env)
{
	size_t	args_count;
	long	ret;

	args_count = 0;
	while (cmd->args && cmd->args[args_count])
		args_count++;
	if (args_count > 2)
	{
		ft_dprintf_str(STDERR_FILENO, "%sexit: too many arguments\n", HEADER);
		return (1);
	}
	else if (args_count <= 1)
		ret = 0;
	else
		ret = ft_atol_sample(cmd->args[1]);
	ft_dprintf_str(STDERR_FILENO, "exit\n");
	ret = check_errors(cmd->args[1], ret);
	free_commands(cmd);
	free_strlist(env);
	exit(ret);
}
