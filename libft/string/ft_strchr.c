/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:08:00 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:08:02 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (str[i] && (unsigned char) str[i] != (unsigned char) c)
		i++;
	if ((unsigned char) str[i] == (unsigned char) c)
		return ((char *) &str[i]);
	return (NULL);
}
