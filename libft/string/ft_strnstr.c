/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:12:44 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:03:12 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strnstr(const char	*str, const char	*to_find, size_t len)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	if (!str)
		return (NULL);
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		while (to_find[z] == str[i + z] && i + z < len)
		{
			if (to_find[z + 1] == '\0')
				return ((char *)&str[i]);
			z++;
		}
		z = 0;
		i++;
	}
	return (NULL);
}
