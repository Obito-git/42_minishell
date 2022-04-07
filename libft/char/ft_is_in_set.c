/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:32:23 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/07 15:32:23 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_is_in_set(char c, char *set)
{
	if (set)
	{
		while (*set)
		{
			if (c == *set)
				return (true);
			set++;
		}
	}
	return (false);
}
