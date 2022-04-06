/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:30:18 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/06 16:30:18 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *cmd, t_strlist *env)
{
	char	**args;
	bool	newline;

	(void) env;
	newline = true;
	args = (char **)cmd->args;
	if (!*args)
		return (0);
	args++;
	if (*args && !ft_strncmp(*args, "-n", ft_strlen(*args)))
	{
		newline = false;
		args++;
	}
	while (*args)
	{
		write(STDOUT_FILENO, *args, ft_strlen(*args));
		if (*(args + 1))
			write(STDOUT_FILENO, " ", 1);
		args++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
