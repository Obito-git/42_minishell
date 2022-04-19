/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:02:06 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:02:06 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_command *cmd, t_strlist *env)
{
	t_strlist	var_list;

	(void) cmd;
	var_list = *env;
	while (var_list.size--)
	{
		printf("%s\n", var_list.head->str);
		var_list.head = var_list.head->next;
	}
	return (0);
}
