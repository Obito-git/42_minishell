/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:52:16 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:52:16 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

int	pwd(t_command *cmd, t_strlist *env)
{
	(void) cmd;
	if (!env->current_path)
	{
		perror("Unable to get filesystem path for current directory");
		return (-1);
	}
	write(STDOUT_FILENO, env->current_path, ft_strlen(env->current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
