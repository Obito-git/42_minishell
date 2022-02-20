/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_threejoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:06:44 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/24 09:06:49 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_str_threejoin(char const *s1, char const *s2, char const *s3)
{
	char	*res;

	if (!s1 || !s2)
		return (ft_strdup(""));
	res = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	if (!res)
		return (NULL);
	res[0] = 0;
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	ft_strcat(res, s3);
	return (res);
}
