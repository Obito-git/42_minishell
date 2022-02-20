/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:51:04 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:51:36 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static size_t	get_str_count(char const *str, char delim)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delim)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != delim)
			i++;
	}
	return (count);
}

static size_t	get_len(char const *str, char delim)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	y;
	size_t	i;

	i = 0;
	y = 0;
	if (!s)
		return (NULL);
	res = (char **) malloc((get_str_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			res[y] = (char *) malloc(get_len(&s[i], c) + 1);
			ft_strlcpy(res[y], &s[i], get_len(&s[i], c) + 1);
			y++;
			i += get_len(&s[i], c);
		}	
	}
	res[y] = NULL;
	return (res);
}
