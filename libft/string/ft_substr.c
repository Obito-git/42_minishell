/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:29:04 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:29:45 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	correct_len;

	if (!s || start >= ft_strlen(s))
		return (ft_strdup(""));
	correct_len = len;
	if (correct_len > ft_strlen(&s[start]))
		correct_len = ft_strlen(&s[start]);
	res = (char *) malloc(correct_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s[start], len + 1);
	return (res);
}
