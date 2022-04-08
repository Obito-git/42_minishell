/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

void	set_quote_mode(const char c, bool q[2])
{
	const int	sq = 0;
	const int	dq = 1;

	if (c == '\'' && q[dq] == false)
	{
		if (q[sq])
			q[sq] = false;
		else
			q[sq] = true;
	}
	else if (c == '\"' && q[sq] == false)
	{
		if (q[dq])
			q[dq] = false;
		else
			q[dq] = true;
	}
}
