/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 05:17:39 by sloquet           #+#    #+#             */
/*   Updated: 2022/01/29 14:02:21 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_write.h"

static size_t	st_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putx(int n, char *s)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, s, st_strlen(s));
		i++;
	}
}

void	ft_putxnl(int n, char *s)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, s, st_strlen(s));
		i++;
	}
	ft_putnl();
}
