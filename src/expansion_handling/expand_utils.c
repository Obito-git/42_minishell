/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

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

int	next_any_quote(char *str, int i)
{
	while (str[i] && !ft_is_in_set(str[i], "\'\""))
		i++;
	return (i);
}

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
