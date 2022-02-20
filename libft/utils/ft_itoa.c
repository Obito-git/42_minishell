/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:52:03 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:52:28 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	get_numblen(long n)
{
	int	size;

	size = 1;
	if (n == LONG_MIN - 1)
		return (20);
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	check_negative(char *str, int *last_index, long *n)
{
	if (*n == LONG_MIN - 1)
	{
		ft_strcpy(str, "-9223372036854775808");
		return (1);
	}
	if (*n < 0)
	{
		*last_index = 1;
		str[0] = '-';
		*n *= -1;
	}
	return (0);
}

char	*ft_itoa(long n)
{
	int		numb_size;
	char	*res;
	int		last_index;

	numb_size = get_numblen(n);
	last_index = 0;
	res = (char *) malloc(numb_size + 1);
	if (!res)
		return (NULL);
	res[numb_size--] = 0;
	if (check_negative(res, &last_index, &n))
		return (res);
	while (numb_size >= last_index)
	{
		res[numb_size] = n % 10 + '0';
		n /= 10;
		numb_size--;
	}
	return (res);
}
