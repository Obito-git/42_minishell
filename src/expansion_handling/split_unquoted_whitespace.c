/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_unquoted_whitespace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:18 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:18 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_strarray_and_set_to_null(char ***dir, long i)
{
	while (i-- >= 0)
		free((*dir)[i]);
	free(*dir);
	*dir = NULL;
}

static const char	*next_sep(const char *str, char *set, bool *quotes)
{
	const int	sq = 0;
	const int	dq = 1;

	while (str && *str && ((quotes[sq] || quotes[dq])
			|| (!ft_is_in_set(*str, set) && !quotes[sq] && !quotes[dq])))
	{
		set_quote_mode(*str, quotes);
		str++;
	}
	return (str);
}

//Finding a quote or whitespace makes it stop
static const char	*next_word(const char *str, char *set, bool quotes[2])
{
	(void)quotes;
	while (str && *str && !ft_is_in_set(*str, "\'\"") && ft_is_in_set(*str, set))
		str++;
	return (str);
}

static char	**strarray_alloc(const char *s, char *set)
{
	size_t	size;
	char	**ret;
	bool	quotes[2];

	if (!s)
		return (NULL);
	ft_bzero(quotes, 2 * sizeof(bool));
	size = 1;
	s = next_word(s, set, quotes);
	while (*s)
	{
		s = next_sep(s, set, quotes);
		s = next_word(s, set, quotes);
		size++;
	}
	ret = ft_calloc(size + 1, sizeof(char *));
	return (ret);
}

char	**split_on_unquoted_whitespace(char const *s, char *set)
{
	char		**str_array;
	const char	*follower;
	long		i;
	bool		quotes[2];

	ft_bzero(quotes, 2 * sizeof(bool));
	str_array = strarray_alloc(s, set);
	s = next_word(s, set, quotes);
	follower = s;
	i = 0;
	if (!str_array)
		return (NULL);
	if (!*s)
		str_array[i++] = ft_strdup("");
	while (str_array && *s)
	{
		s = next_sep(s, set, quotes);
		str_array[i] = ft_strndup(follower, s - follower);
		if (!str_array[i])
			free_strarray_and_set_to_null(&str_array, i);
		s = next_word(s, set, quotes);
		follower = s;
		i++;
	}
	return (str_array);
}
