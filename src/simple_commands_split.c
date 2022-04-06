#include "minishell.h"

static void	free_str_array_and_set_to_null(char ***dir, long i)
{
	while (i-- >= 0)
		free((*dir)[i]);
	free(*dir);
	*dir = NULL;
}

static void	set_quote_mode(const char *c, bool *q)
{
	const int	sq = 0;
	const int	dq = 1;

	if (c)
	{
		if (*c == '\'')
		{
			if (q[sq])
				q[sq] = false;
			else
				q[sq] = true;
		}
		else if (*c == '\"')
		{
			if (q[dq])
				q[dq] = false;
			else
				q[dq] = true;
		}
	}
}

static const char	*next_sep(const char *str, char *set, bool *quotes)
{
	const int	sq = 0;
	const int	dq = 1;

	while (str && *str && ((quotes[sq] || quotes[dq])
			|| (!ft_is_in_set(*str, set) && !quotes[sq] && !quotes[dq])))
	{
		set_quote_mode(str, quotes);
		str++;
	}
	return (str);
}

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

#include <string.h> //Replace strndup !
char	**split_on_unquoted_redir(char const *s, char *set)
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
		str_array[i] = strndup(follower, s - follower);
		follower = s;
		if (!str_array[i])
			free_str_array_and_set_to_null(&str_array, i);
		i++;
		if (*s)
		{
			s = next_word(s, set, quotes);
			str_array[i] = strndup(follower, s - follower);
			if (!str_array[i])
				free_str_array_and_set_to_null(&str_array, i);
			follower = s;
			i++;
		}
	}
	return (str_array);
}
