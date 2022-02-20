/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:02:21 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:02:23 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	char	tmp;
	size_t	str_len;

	i = 0;
	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	while (i < str_len - 1 - i)
	{
		tmp = str[i];
		str[i] = str[str_len - 1 - i];
		str[str_len - 1 - i] = tmp;
		i++;
	}
	return (str);
}
