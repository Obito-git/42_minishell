/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_is_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:56:50 by tpouget           #+#    #+#             */
/*   Updated: 2022/03/30 13:56:50 by tpouget          ###   ########.fr       */
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
