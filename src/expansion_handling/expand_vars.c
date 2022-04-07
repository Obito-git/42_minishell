#include "minishell.h"

static int	get_len_non_expandable_from_index_table(int *indexes)
{
	int		i;
	int		y;
	size_t	len;

	len = 0;
	i = 0;
	y = 1;
	while (indexes[y] != 0)
	{
		if (indexes[y] == -1)
		{
			y += 2;
			i += 2;
			continue ;
		}
		len += indexes[y] - indexes[i];
		i++;
		y++;
	}
	return (len);
}

static int	get_expanded_len(t_strlist *exp_list, int *indexes)
{
	int	total_len;

	total_len = 0;
	total_len += get_strlist_total_len(*exp_list);
	total_len += get_len_non_expandable_from_index_table(indexes);
	return (total_len);
}

static t_strlist	*get_expansions_list(char *to_exp, int *indexes, t_strlist *env)
{
	t_strlist	*exp_list;
	char		*var;
	int			i;
	int			y;

	exp_list = new_strlist();
	i = 0;
	y = 1;
	while (1)
	{
		while (indexes[y] == -1)
			y++;
		if (indexes[y] == 0)
			break ;
		var = get_env_var_val_from_slice(&to_exp[indexes[i]],
				&to_exp[indexes[y]], env);
		append_str_to_strlist(exp_list, var);
		i = y;
		y++;
	}
	return (exp_list);
}

/*Receives an index array following a certain format then and uses to create */
/*a string. The format is the following. Each index marks the (including)*/
/*start of a token and the (excluding) end of the one that came before. */
/*If the index is -1 it means that instead of copying the slice defined by the */
/*index before and after it, the function must the value of an evironment */
/*variable*/
static char	*expand_str_from_index_table(char *to_exp, int *idxs, t_strlist *env)
{
	char		*exp_str;
	t_strlist	*exp;
	int			y;
	int			i;

	exp = get_expansions_list(to_exp, idxs, env);
	exp_str = malloc(get_expanded_len(exp, idxs) + 1);
	if (exp_str == NULL)
		return (NULL);
	exp_str[0] = 0;
	i = 0;
	y = 1;
	while (idxs[y] != 0)
	{
		if (idxs[y] == -1)
		{
			if (exp->head)
			{
				ft_strcat_slice(exp_str, exp->head->str, exp->head->len);
				exp->head = exp->head->next;
			}
			y++;
			i = y;
		}
		else
		{
			ft_strcat_slice(exp_str, &to_exp[idxs[i]], idxs[y] - idxs[i]);
			i = y;
			y++;
		}
	}
	free_strlist(exp);
	return (exp_str);
}

char	**expand_strings_depending_on_first_char(char **argv, t_strlist *env)
{
	int		i;
	int		*indexes;
	char	*to_free;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] && argv[i][0] != '\'' )
		{
			to_free = argv[i];
			indexes = register_expansions(argv[i]);
			argv[i] = expand_str_from_index_table(argv[i], indexes, env);
			free(indexes);
			if (argv[i] == NULL)
			{
				//Risks of double-free
				/*while (--i)*/
				/*    free (argv[i]);*/
				return (NULL);
			}
			free(to_free);
		}
		i++;
	}
	return (argv);
}
