#include "minishell.h"
#include "libft.h"

//returns next argument. working with ft_minishell_split
char	*get_next_arg(char *s, int *i, int *z)
{
	char	*res;
	char	*tmp;

	tmp = ft_substr(s, *z, *i - *z + 1);
	if (!tmp)
		return (NULL);
	while (s[*i] && s[*i + 1] && s[*i + 1] == ' ')
		*i += 1;
	res = ft_strtrim(tmp, " ");
	free(tmp);
	/*
	while (res && ft_strlen(res) > 0
			&& ((res[0] == '\"' && res[ft_strlen(res) - 1] == '\"')
			|| (res[0] == '\'' && res[ft_strlen(res) - 1] == '\'')))
	{
		if (res[0] == '\"')
			tmp = ft_strtrim(res, "\"");
		else
			tmp = ft_strtrim(res, "\'");
		free(res);
		if (!tmp)
			return (NULL);
		res = tmp;
	} */
	return (res);
}

//working like split but not touching the content inside quotes;
//used for not touch delimiter (space) inside quotes
//also deleting all external quotes for execev (it takes args without ""'')
char	**ft_minishell_split(char **res, char *s, int z, int i)
{
	int		y;
	bool	q;
	bool	dq;

	res = (char **) malloc(sizeof(char *) * (z + 1));
	q = false;
	dq = false;
	z = 0;
	i = 0;
	y = 0;
	while (res && s[i])
	{
		set_quotes(s[i], &q, &dq);
		if ((s[i] == ' ' && !q && !dq) || !s[i + 1])
		{
			res[y++] = get_next_arg(s, &i, &z);
			if (!res[y - 1])
				return (free_strarray(res));
			z = i;
		}
		res[y] = NULL;
		i++;
	}
	return (res);
}

//applies ft_strtrim on every string of the array
//if malloc error, all memory will be freed
char	**ft_strtrim_array(char **s, char *set)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	if (!s || !set)
		return (NULL);
	while (s[i])
	{
		tmp = ft_strtrim(s[i], set);
		if (!tmp)
		{
			y = 0;
			while (s[y])
				free(s[y++]);
			free(s);
			return (NULL);
		}
		free(s[i]);
		s[i] = tmp;
		i++;
	}
	return (s);
}

//applies free on every string of the array
//return NULL for save some lines for the normes
char	**free_strarray(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}
