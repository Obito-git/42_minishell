/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:25:26 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:27:53 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_check(char *numb, long *sign)
{
	size_t	i;

	i = 0;
	*sign = 1;
	if (numb[i] == '-')
	{
		*sign = -1;
		i++;
	}
	if (ft_strlen(&numb[i]) > 19 || numb[i] == '0')
		return (0);
	if ((ft_strlen(numb) == 20
			&& ft_strcmp("-9223372036854775808", numb) < 0)
		|| (i == 0 && ft_strlen(numb) == 19
			&& ft_strcmp("9223372036854775807", numb) < 0))
		return (0);
	while (numb[i] && ft_isdigit(numb[i]))
		i++;
	return (numb[i] == 0);
}

long	ft_atol_sample(char *numb)
{
	long	res;
	size_t	i;
	long	sign;

	res = 0;
	i = 0;
	if (!ft_check(numb, &sign))
		return (0);
	if (numb[i] == '-')
		i++;
	while (numb[i])
	{
		res += (numb[i] - '0') * ft_pow(10, ft_strlen(&numb[i]) - 1);
		i++;
	}
	return (res * sign);
}
