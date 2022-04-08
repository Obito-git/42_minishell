/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_expansions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* Does log no matter what */
enum e_expand_state	normal_mode(char *str, int *i, int **table)
{
	log_index(*i, table);
	*i = next_var(str, *i);
	if (str[*i] == 0)
		return (done);
	if (str[*i] == '$')
		return (var_start);
	return (-1);
}

/* Does log no matter what */
enum e_expand_state	var_start_mode(char *str, int *i, int **table)
{
	(void)str;
	log_index(*i, table);
	(*i)++;
	return (in_var);
}

/* Does not log */
enum e_expand_state	in_var_mode(char *str, int *i, int **table)
{
	log_index(-1, table);
	if (is_special_var_start_char(str[*i]))
			(*i)++;
	else
		*i = next_non_env_var(str, *i);
	if (str[*i] == '$' && !is_single_dollar(&str[*i]))
		return (var_start);
	else
		return (normal);
}

int	*register_expansions(char *to_exp)
{
	int					*indexes;
	int					*box;
	int					i;
	enum e_expand_state	state;

	indexes = malloc(4096 * sizeof(int));
	if (!indexes)
		return (NULL);
	i = 0;
	*indexes = 0;
	if (to_exp[0] == DOLLAR && !is_single_dollar(to_exp))
		state = var_start;
	else
		state = normal;
	box = indexes;
	while (state != done)
		state = g_expand_func_table[state](to_exp, &i, &box);
	log_index(i, &box);
	log_index(0, &box);
	return (indexes);
}
