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
#include "../libft.h"

static int	get_int_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	return (i);
}

static int	iscorrect_format(const char *s, size_t *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (s[*i] == '+')
		*i += 1;
	else if (s[*i] == '-')
	{
		*sign = -1;
		*i += 1;
	}
	if (!ft_isdigit(s[*i]))
		return (0);
	return (1);
}

int	ft_atoi(const char *s)
{
	size_t	i;
	int		sign;
	long	res;
	int		y;
	int		temp;

	res = 0;
	if (!iscorrect_format(s, &i, &sign)
		|| (get_int_len(&s[i]) > 10 && sign == -1))
		return (0);
	if (get_int_len(&s[i]) > 10 && sign == 1)
		return (-1);
	while (get_int_len(&s[i]) > 0)
	{
		y = 1;
		temp = 1;
		while (y++ < get_int_len(&s[i]))
			temp *= 10;
		res += temp * (s[i] - '0');
		if ((sign == -1 && res > 2147483648)
			|| (sign == 1 && res > 2147483647))
			return (0);
		i++;
	}
	return ((int)(res * sign));
}	
