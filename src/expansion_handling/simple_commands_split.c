/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands_split.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*next_sep(const char *str, const char *set, bool *quotes)
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

static const char	*next_word(const char *str, const char *set, bool quotes[2])
{
	(void)quotes;
	while (str && *str && !ft_is_in_set(*str, "\'\"") && ft_is_in_set(*str, set))
		str++;
	return (str);
}

static char	**strarray_alloc(const char *s, const char *set)
{
	size_t	size;
	char	**ret;
	bool	quotes[2];

	if (!s)
		return (NULL);
	quotes[0] = 0;
	quotes[1] = 0;
	size = 1;
	s = next_word(s, set, quotes);
	while (*s)
	{
		s = next_sep(s, set, quotes);
		size++;
		s = next_word(s, set, quotes);
		size++;
	}
	ret = ft_calloc(size + 1, sizeof(char *));
	return (ret);
}

/*Splitting pattern goes like this :*/
/*1. Set following cursor to cursor*/
/*2. Cursor goes to next sep in set or word*/
/*3. Copy the slice[follower, s] into str_array*/
static const char	*split_next(
		char **str_array, const char *s, int *i, bool quotes[2])
{
	const char	*follower;
	const char	*set = "|<>";

	follower = s;
	s = next_sep(s, set, quotes);
	str_array[*i] = ft_strndup(follower, s - follower);
	if (!str_array[*i])
		return (NULL);
	(*i)++;
	if (*s)
	{
		follower = s;
		s = next_word(s, set, quotes);
		str_array[*i] = ft_strndup(follower, s - follower);
		if (!str_array[*i])
			return (NULL);
		(*i)++;
	}
	return (s);
}

char	**split_on_unquoted_redir(char const *s)
{
	char		**str_array;
	const char	*follower;
	int			i;
	bool		quotes[2];
	const char	*set = ">|<";

	i = 0;
	ft_bzero(quotes, sizeof(quotes));
	str_array = strarray_alloc(s, set);
	if (!str_array)
		return (NULL);
	if (*s == 0)
		str_array[i++] = ft_strdup("");
	follower = s;
	s = next_word(s, set, quotes);
	if (s - follower > 0)
		str_array[i++] = ft_strndup(follower, s - follower);
	while (s && *s)
		s = split_next(str_array, s, &i, quotes);
	if (s)
		return (str_array);
	while (i-- >= 0)
		free(str_array[i]);
	free(str_array);
	return (NULL);
}
