#include "minishell.h"
#include "quote_splitting.h"

//Erase
#include <assert.h>
#include <string.h>
#include <stdio.h>
//Erase this above !

/*enum e_quote_state {*/
/*    not_in_quote,*/
/*    single_quote,*/
/*    double_quote,*/
/*    fini,*/
/*};*/

static enum e_quote_state	(*g_quote_func_table[])(char *, int*, int**) = {
	&not_in_quote_mode,
	&sq_mode,
	&dq_mode,
};

int	next_any_quote(char *str, int i)
{
	while (str[i] && !ft_is_in_set(str[i], "\'\""))
		i++;
	return (i);
};

int	next_double_quote(char *str, int i)
{
	while (str[i] && str[i] != '\"')
		i++;
	return (i);
}

int	next_single_quote(char *str, int i)
{
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

static void	log_index(int i, int **table)
{
	**table = i;
	*table += 1;
}

enum e_quote_state	not_in_quote_mode(char *str, int *i, int **table)
{
	(*i)++;
	*i = next_any_quote(str, *i);
	if (str[*i] == 0)
	{
		log_index(*i, table);
		return (fini);
	}
	log_index(*i, table);
	if (str[*i] == '\'')
		return (single_quote);
	if (str[*i] == '\"')
		return (double_quote);
	assert(false);
	return (-1);
}

enum e_quote_state	sq_mode(char *str, int *i, int **table)
{
	assert(str[*i] == '\'');
	(*i)++;
	*i = next_single_quote(str, *i);
	if (str[*i] == 0)
	{
		//false alert,  this is not a valid single quote, remove prvious index
		(*table)--;
		log_index(*i, table);
		return (fini);
	}
	log_index(*i + 1, table);
	if (str[*i + 1] == 0)
		return (fini);
	return (not_in_quote);
}

enum e_quote_state	dq_mode(char *str, int *i, int **table)
{
	assert(str[*i] == '\"');
	(*i)++;
	*i = next_double_quote(str, *i);
	if (str[*i] == 0)
	{
		//false alert,  this is not a valid double quote, remove prvious index
		(*table)--;
		log_index(*i, table);
		return (fini);
	}
	log_index(*i + 1, table);
	if (str[*i + 1] == 0)
		return (fini);
	return (not_in_quote);
}

int	*register_quotes(char *str)
{
	int	*indexes;
	int	*box;
	enum e_quote_state	state;
	int	i;

	indexes = malloc(4096 * sizeof(int));
	if (!indexes || !str)
		return (NULL);
	if (str[0] == '\'')
		state = single_quote;
	else if (str[0] == '\"')
		state = double_quote;
	else
		state = not_in_quote;
	i = 0;
	box = indexes;
	log_index(0, &box);
	while (*str && state != fini)
		state = g_quote_func_table[state](str, &i, &box);
	log_index(0, &box);
	return (indexes);
}

static char *_next_any_quote(char *str)
{
	while (*str && *str != '\'' && *str != '\"')
		str++;
	return (str);
}

int		check_quotes(char *str)
{
	char quote;

	if (*str == '\'' || *str == '\"')
		quote = *str;
	else
		quote = 0;
	while (*str)
	{
		if (quote == 0)
		{
			str = _next_any_quote(str);
			quote = *str;
		}
		else
		{
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == 0)
				return (-1);
			else
				quote = 0;
			str++;
		}
	}
	return (0);
}

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
	int 	i;

	i = 0;
	n = 1;
	while (index_table[++i] != 0)
		n++;
	ret = malloc(n * sizeof(char *) + 1);
	/*printf("Allocated for %li strings\n", n);*/
	return (ret);
}

char	**quote_preserving_split_splitter(char *str, int *index_table)
{
	char		**strarray;
	size_t		i;
	size_t		y;
	size_t		z;

	strarray = strarray_alloc_from_index_table(index_table);
	if (!str || !strarray)
		return (NULL);
	i = 0;
	y = 1;
	z = 0;
	while (strarray && index_table[y] != 0)
	{
		strarray[z] = strndup(&str[index_table[i]], index_table[y]- index_table[i]);
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
	int *index_table;
	char **str_array;

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

