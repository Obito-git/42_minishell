#include "minishell.h"

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
