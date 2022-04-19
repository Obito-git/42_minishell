/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:01:51 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:01:51 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_status(int wstatus)
{
	int	status;

	status = wstatus;
	if (WIFEXITED(wstatus))
		status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		status = 128 + WTERMSIG(wstatus);
	return (status);
}
