#include "minishell.h"

static void	free_strarray_and_set_to_null(char ***strarray, long i)
{
	while (i-- >= 0)
		free((*strarray)[i]);
	free(*strarray);
	*strarray = NULL;
}

static char	**strarray_alloc_from_index_table(int *index_table)
{
	size_t	n;
	char	**ret;
	int		i;

	i = 0;
	n = 1;
	while (index_table[++i] != 0)
		n++;
	ret = malloc(n * sizeof(char *) + 1);
	return (ret);
}

char	**quote_preserving_split_splitter(char *str, int *idx_table)
{
	char		**strarray;
	size_t		i;
	size_t		y;
	size_t		z;

	strarray = strarray_alloc_from_index_table(idx_table);
	if (!str || !strarray)
		return (NULL);
	i = 0;
	y = 1;
	z = 0;
	while (strarray && idx_table[y] != 0)
	{
		strarray[z] = ft_strndup(
				&str[idx_table[i]], idx_table[y] - idx_table[i]);
		if (strarray[z] == NULL)
			free_strarray_and_set_to_null(&strarray, y);
		i++;
		y++;
		z++;
	}
	if (strarray)
		strarray[z] = NULL;
	return (strarray);
}

char	**quote_preserving_split(char *str)
{
	int		*index_table;
	char	**str_array;

	if (str == NULL)
		return (NULL);
	if (check_quotes(str) == -1)
	{
		ft_dprintf_str(STDERR_FILENO, "\e[31mYou have unclosed quotes$\e[0m\n");
		return (NULL);
	}
	index_table = register_quotes(str);
	if (index_table == NULL)
	{
		free(index_table);
		return (NULL);
	}
	str_array = quote_preserving_split_splitter(str, index_table);
	free(index_table);
	if (str_array == NULL)
		return (NULL);
	return (str_array);
}

/*int main()*/
/*{*/
/*    char *user_input = NULL;*/
/*    char **str_array = NULL;*/
/*    char **iter = NULL;*/
/*    int	*index_table = NULL;*/

/*    while (1)*/
/*    {*/
/*        user_input = readline("012345678901234567890123456789\n");*/
/*        printf("%i\t", index_table[0]);*/
/*        for (int i = 1; index_table[i] != 0; i++)*/
/*            printf("%i\t", index_table[i]);*/
/*        printf("\n");*/
/*        free(index_table);*/
/*        iter = str_array;*/
/*        while(iter && *iter)*/
/*        {*/
/*            printf("%s\n", *iter);*/
/*            iter++;*/
/*        }*/
/*        iter = str_array;*/
/*        while (iter && *iter)*/
/*        {*/
/*            free(*iter);*/
/*            iter++;*/
/*        }*/
/*        free(str_array);*/
/*        free(user_input);*/
/*    }*/

/*}*/
