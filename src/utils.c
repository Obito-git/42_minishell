#include "minishell.h"

void	print_strarray(char **com)
{
	//FIXME (delete this func)
	if (com)
	{
		while (*com)
		{
			printf("%s\n", *com);
			com++;
		}
	}
}

/* This function will always null terminate past n bytes so make sure you
 * allocate for the null byte at the end or it will overflow 				*/
char	*ft_strcat_slice(char *dest, const char *src, int n)
{
	size_t		i;
	size_t		y;
	const char	*end;

	if (dest && src && n > 0)
	{
		i = 0;
		y = ft_strlen(dest);
		end = src + n;
		while (src[i] && &src[i] != end)
		{
			dest[y] = src[i];
			i++;
			y++;
		}
		dest[y] = '\0';
	}
	return (dest);
}

char	*ft_join_null_terminated_str_array(char **str_array)
{
	char	*ret;
	size_t	total_len;
	int		i;

	if (!str_array)
		return (NULL);
	total_len = 0;
	i = 0;
	while (str_array[i])
	{
		total_len += ft_strlen(str_array[i]);
		i++;
	}
	ret = malloc(total_len + 1);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	i = 0;
	while (str_array[i])
	{
		ft_strcat(ret, str_array[i]);
		i++;
	}
	return (ret);
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
