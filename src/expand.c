#include "minishell.h"
#include "expansion.h"

//Remove this !
#include <assert.h>

bool	is_special_var_start_char(int c)
{
	if (c == '?'
		|| c == '$'
		|| c == '@'
		|| c == '#'
		|| c == '!'
		|| c == '-'
		|| c == '*'
		|| c == '_'
		|| ft_isdigit(c))
		return (true);
	return (false);
}

bool	is_valid_shellvar_start_char(int c)
{
	if (ft_isdigit(c))
		return (false);
	if (is_special_var_start_char(c) || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_valid_env_var_char(int c)
{
	if (c == '_' || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_single_dollar(char *c)
{
	if (c[0] == '$')
		if (!is_valid_shellvar_start_char(c[1]))
			return (true);
	return (false);
}

int	get_len_non_expandable_from_indexes(int *indexes)
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

int	get_expanded_len(t_strlist *exp_list, int *indexes)
{
	int	total_len;

	total_len = 0;
	total_len += get_strlist_total_len(*exp_list);
	total_len += get_len_non_expandable_from_indexes(indexes);
	return (total_len);
}

t_strlist	*get_expansions_list(char *to_exp, int *indexes, t_strlist *env)
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
				&to_exp[indexes[y]], env->envp);
		append_str_to_strlist(exp_list, var);
		i = y;
		y++;
	}
	return (exp_list);
}

/*enum e_expand_state {	*/
/*    normal = 0,		*/
/*    var_start,		*/
/*    in_var,			*/
/*    done,				*/
/*};					*/

static enum e_expand_state	(*g_expand_func_table[])(char *, int*, int**) = {
	&normal_mode,
	&var_start_mode,
	&in_var_mode,
};

/* Goes to next dollar that is not a single dollar */
int	next_var(char *str, int i)
{
	while (str[i] && (is_single_dollar(&str[i]) || str[i] != DOLLAR))
		i++;
	return (i);
}

/* Does not account for $ or any special char */
int	next_non_env_var(char *str, int i)
{
	while (is_valid_env_var_char(str[i]))
		i++;
	return (i);
}

static void	log_index(int i, int **table)
{
	**table = i;
	*table += 1;
}

/* Does log no matter what */
enum e_expand_state	normal_mode(char *str, int *i, int **table)
{
	//Log current index
	log_index(*i, table);
	*i = next_var(str, *i);
	//Check for end
	if (str[*i] == 0)
		return (done);
	if (str[*i] == '$')
		return (var_start);
	assert(false);
	return (-1);
}

/* Does log no matter what */
enum e_expand_state	var_start_mode(char *str, int *i, int **table)
{
	assert(str[*i] == '$');
	//Log current index Normal mode is responsible that it is not an isolated var
	log_index(*i, table);
	//Jump over dollar
	(*i)++;
	return (in_var);
}

/* Does not log */
enum e_expand_state	in_var_mode(char *str, int *i, int **table)
{
	//Put in table that it's a var we are dealing with
	log_index(-1, table);
	//Jumping over the right size of char
	if (is_special_var_start_char(str[*i]))
			(*i)++;
	else
		*i = next_non_env_var(str, *i); //Has to stop on dollars
	if (str[*i] == '$' && !is_single_dollar(&str[*i]))
		return (var_start);
	else
		return (normal);
}

int	*register_expansions(char *to_exp)
{
	int	*indexes;
	int	*box;
	int	i;
	enum e_expand_state state;

	indexes = malloc(4096 * sizeof(int));
	if (!indexes)
		return (NULL);
	i = 0;
	/*if (to_exp[0] == '\"' || to_exp[0] == '\'')*/
	/*    i = 1;*/
	*indexes = 0;
	if (to_exp[0] == DOLLAR && !is_single_dollar(to_exp))
		state = var_start;
	else
		state = normal;
	box = indexes;
	while (state != done)
		state = g_expand_func_table[state](to_exp, &i, &box);
	/*if (i > 0 && (to_exp[i - 1] == '\"' || to_exp[i - 1] == '\''))*/
	/*    log_index(i - 1, &box);*/
	/*else*/
	log_index(i, &box);
	log_index(0, &box);
	return (indexes);
}

char	*expand_arg(char *to_exp, int *indexes, t_strlist *env)
{
	char		*exp_str;
	t_strlist	*exp;
	int			y;
	int			i;

	exp = get_expansions_list(to_exp, indexes, env);
	exp_str = malloc(get_expanded_len(exp, indexes) + 1);
	if (exp_str == NULL)
		return (NULL);
	exp_str[0] = 0;
	i = 0;
	y = 1;
	while (indexes[y] != 0)
	{
		if (indexes[y] == -1)
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
			ft_strcat_slice(exp_str, &to_exp[indexes[i]], indexes[y] - indexes[i]);
			i = y;
			y++;
		}
	}
	free_strlist(exp);
	return (exp_str);
}

char	**expand_args(char **argv, t_strlist *env)
{
	int	i;
	int	*indexes;
	char *to_free;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] && argv[i][0] != '\'' )
		{
			to_free = argv[i];
			indexes = register_expansions(argv[i]);
			argv[i] = expand_arg(argv[i], indexes, env);
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
