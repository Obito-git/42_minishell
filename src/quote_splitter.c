#include "minishell.h"

#include <string.h>
//Erase this above !

static void	free_strarray_and_set_to_null(char ***strarray, long i)
{
	while (i-- >= 0)
		free((*strarray)[i]);
	free(*strarray);
	*strarray = NULL;
}

static const char	*next_quote(const char *str, char *mode)
{
	if (*mode != '\'' && *mode != '\"')
	{
		while (*str && (*str != '\'' || *str != '\"'))
			str++;
		*mode = *str;
		return (str);
	}
	else
	{
		while (*str && *str != *mode)
			str++;
		*mode = *str;
		return (str);
	}
	return (str);
}

static char	**strarray_alloc(const char *s, char c)
{
	size_t	size;
	char	**ret;

	if (!s)
		return (NULL);
	size = 1;
	s = next_word(s, c);
	while (*s)
	{
		s = next_sep(s, c);
		s = next_word(s, c);
		size++;
	}
	ret = malloc(size * sizeof(char *));
	return (ret);
}

static char **bullshit_function(char *s, char *follower, char mode, char **strarray)
{
	follower = s;
	s = next_quote(s, &mode);
	if (mode == '\"' | mode == '\"')
		strarray[i] = strndup(follower, s - follower - 1);
	else
		strarray[i] = strndup(follower + 1, s - follower);
	while (strarray && *s)
	{
		s = next_quote(s, &mode);
		if (mode == '\"' | mode == '\"')
			strarray[i] = strndup(follower + 1, s - follower - 1);
		else													// What if follower - 1 is just before str ?
			strarray[i] = strndup(follower - 1, s - follower + 1); //No need to worry about overflow but we have an undeflow problem
		if (!strarray[i])
			free_strarray_and_set_to_null(&strarray, i);
		follower = s;
		i++;
	}
	if (strarray)
		strarray[i] = NULL;
}

char	**quote_preserving_split(char const *s)
{
	char		**strarray;
	char		*follower;
	long		i;
	char		mode;

	mode = *s;
	strarray = strarrayalloc(s);
	i = 0;
	if (!strarray)
		return (NULL);
	if (strarray && !*s)
		strarray[i++] = ft_strdup("");
	follower = s;
	s = next_quote(s, &mode);
	if (mode == '\"' | mode == '\"')
		strarray[i] = strndup(follower, s - follower - 1);
	else
		strarray[i] = strndup(follower + 1, s - follower);
	while (strarray && *s)
	{
		s = next_quote(s, &mode);
		if (mode == '\"' | mode == '\"')
			strarray[i] = strndup(follower + 1, s - follower - 1);
		else													// What if follower - 1 is just before str ?
			strarray[i] = strndup(follower - 1, s - follower + 1); //No need to worry about overflow but we have an undeflow problem
		if (!strarray[i])
			free_strarray_and_set_to_null(&strarray, i);
		follower = s;
		i++;
	}
	if (strarray)
		strarray[i] = NULL;
	return (strarray);
}

