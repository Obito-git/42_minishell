#include "../minishell.h"

//applies ft_strtrim on every string of the array
//if malloc error, all memory will be freed
char	**ft_strtrim_array(char **s, char *set)
{
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		tmp = ft_strtrim(s[i], set);
		if (!tmp)
		{
			y = 0;
			while (s[y++])
				free(s[y]);
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
void free_strarray(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
