/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:05:47 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:06:39 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static size_t	ft_resultlen(unsigned long nbr, char *base)
{
	size_t	res_len;

	res_len = 1;
	while (nbr % (long) ft_strlen(base) != nbr)
	{
		nbr /= (long) ft_strlen(base);
		res_len++;
	}
	return (res_len);
}

static int	ft_base_check(char	*base)
{
	int	i;
	int	z;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		z = i + 1;
		while (base[z] != '\0')
		{	
			if (base[i] == base[z])
				return (0);
			z++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static char	*transform(unsigned long nbr, char *base)
{
	char	*res;
	size_t	i;

	i = 0;
	res = (char *) ft_calloc((1 + ft_resultlen(nbr, base)), sizeof(char));
	if (!res)
		return (NULL);
	if (nbr == 0)
		res[i] = base[nbr % ft_strlen(base)];
	while (nbr > 0)
	{
		res[i] = base[nbr % ft_strlen(base)];
		nbr = nbr / ft_strlen(base);
		i++;
	}
	return (res);
}

char	*ft_convert_base(unsigned long nbr, char *base)
{
	if (!ft_base_check(base))
		return (NULL);
	return (ft_strrev(transform(nbr, base)));
}
