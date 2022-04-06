#include "minishell.h"

static void	free_dir_and_set_to_null(char ***dir, long i)
{
	while (i-- >= 0)
		free((*dir)[i]);
	free(*dir);
	*dir = NULL;
}

static void	set_quote_mode(const char c, bool *q)
{
	const int	sq = 0;
	const int	dq = 1;

	if (c == '\'' && q[dq] == false)
	{
		if (q[sq])
			q[sq] = false;
		else
			q[sq] = true;
	}
	else if (c == '\"' && q[sq] == false)
	{
		if (q[dq])
			q[dq] = false;
		else
			q[dq] = true;
	}
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

static char	**diralloc(const char *s, char *set)
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

#include <string.h> //Replace strndup !
char	**split_on_unquoted_whitespace(char const *s, char *set)
{
	char		**dir;
	const char	*follower;
	long		i;
	bool		quotes[2];

	ft_bzero(quotes, 2 * sizeof(bool));
	dir = diralloc(s, set);
	s = next_word(s, set, quotes);
	follower = s;
	i = 0;
	if (!dir)
		return (NULL);
	if (!*s)
		dir[i++] = ft_strdup("");
	while (dir && *s)
	{
		s = next_sep(s, set, quotes);
		dir[i] = ft_strndup(follower, s - follower);
		if (!dir[i])
			free_dir_and_set_to_null(&dir, i);
		s = next_word(s, set, quotes);
		follower = s;
		i++;
	}
	return (dir);
}
