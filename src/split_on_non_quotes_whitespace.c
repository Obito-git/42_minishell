#include "minishell.h"

static void	free_dir_and_set_to_null(char ***dir, long i)
{
	while (i-- >= 0)
		free((*dir)[i]);
	free(*dir);
	*dir = NULL;
}

static const char	*next_sep(const char *str, char *set)
{
	char	quote;

	quote = *str;
	while (str && *str)
	{
		if (ft_is_in_set(*str, "\'\"") && quote == *str)
			quote = 0;
		else if (ft_is_in_set(*str, "\'\""))
			quote = *str;
		if (!ft_is_in_set(quote, "\'\""))
		{
			if (!ft_is_in_set(*str, set))
				str++;
		}
		else
			str++;
	}
	return (str);
}

//Finding a quote or whitespace makes it stop
static const char	*next_word(const char *str, char *set)
{
	while (str && *str && !ft_is_in_set(*str, "\'\"") && !ft_is_in_set(*str, set))
		str++;
	return (str);
}

static char	**diralloc(const char *s, char *set)
{
	size_t	size;
	char	**ret;

	if (!s)
		return (NULL);
	size = 1;
	s = next_word(s, set);
	while (*s)
	{
		s = next_sep(s, set);
		s = next_word(s, set);
		size++;
	}
	ret = malloc(size * sizeof(char *));
	return (ret);
}

#include <string.h> //Replace strndup !
char	**split_when_unquote(char const *s, char *set)
{
	char		**dir;
	const char	*follower;
	long		i;

	dir = diralloc(s, set);
	s = next_word(s, set);
	follower = s;
	i = 0;
	if (dir && !*s)
		dir[i++] = ft_strdup("");
	if (!dir)
		return (NULL);
	while (dir && *s)
	{
		s = next_sep(s, set);
		dir[i] = ft_strndup(follower, s - follower);
		if (!dir[i])
			free_dir_and_set_to_null(&dir, i);
		s = next_word(s, set);
		follower = s;
		i++;
	}
	if (dir)
		dir[i] = NULL;
	return (dir);
}

