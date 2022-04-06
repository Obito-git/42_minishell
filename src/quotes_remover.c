#include "minishell.h"

char	*remove_first_and_last_quote(char *str)
{
	int len;
	char *ret;

	len = ft_strlen(str);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
			return (ft_strdup(""));
	if (ft_is_in_set(str[0], "\'\""))
	{
		ft_strcpy(ret, str + 1);
		if (len > 1)
			if (ft_is_in_set(str[len - 1], "\'\""))
				if (len > 2)
					ret[len - 2] = 0;
	}
	else
	{
		ft_strcpy(ret, str);
		if (len > 1)
			if (ft_is_in_set(str[len - 1], "\'\""))
					ret[len - 1] = 0;
	}
	return (ret);
}

char	**remove_first_and_last_quote_on_each_str(char **str_array)
{
	int i;
	char	*to_free;

	if (!str_array)
		return (NULL);
	i = 0;
	while (str_array[i])
	{
		to_free = str_array[i];
		str_array[i] = remove_first_and_last_quote(str_array[i]);
		free(to_free);
		if (!str_array[i])
		{
			while (--i)
				free(str_array[i]);
			free(str_array);
			return (NULL);
		}
		i++;
	}
	return (str_array);
}

char	**handle_quotes(char **strarray)
{
	char *to_free;
	char **split;
	int i;

	i = 0;
	if (!strarray)
		return (NULL);
	while (strarray[i])
	{
		to_free = strarray[i];
		split = quote_preserving_split(strarray[i]);
		free(to_free);
		split = remove_first_and_last_quote_on_each_str(split);
		strarray[i] = ft_join_null_terminated_str_array(split);
		free_strarray(split);
		if (!strarray[i])
		{
			while (--i)
				free(strarray[i]);
			free(strarray);
			return (NULL);
		}
		i++;
	}
	return (strarray);
}
