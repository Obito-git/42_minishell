/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:08:38 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:08:40 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*pos;

	pos = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			pos = (char *)&s[i];
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (pos);
}
