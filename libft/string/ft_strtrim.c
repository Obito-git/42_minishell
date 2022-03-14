/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:44:48 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/23 11:47:23 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static size_t	get_start(char const *s1, char const *set)
{
	size_t	start;
	size_t	y;

	start = 0;
	while (s1[start])
	{
		y = 0;
		while (set[y] && s1[start] != set[y])
			y++;
		if (set[y] == '\0')
			return (start);
		start++;
	}
	return (start);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	y;

	end = ft_strlen(s1) - 1;
	while (end > 0)
	{
		y = 0;
		while (set[y] && s1[end] != set[y])
			y++;
		if (set[y] == '\0')
			return (end);
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (ft_strdup(""));
	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	res = (char *) malloc(end - start + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[start], end - start + 2);
	return (res);
}
