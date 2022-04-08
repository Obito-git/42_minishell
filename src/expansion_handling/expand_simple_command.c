/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	**expand_simple_command(char *simple_command, t_strlist *env)
{
	char	**com;
	char	*expanded;

	com = quote_preserving_split(simple_command);
	if (!com)
		return (NULL);
	com = expand_strings_depending_on_first_char(com, env);
	if (!com)
		return (NULL);
	expanded = ft_join_null_terminated_str_array(com);
	free_strarray(com);
	if (!expanded)
		return (NULL);
	com = split_on_unquoted_whitespace(expanded, " \t");
	free(expanded);
	if (!com)
		return (NULL);
	com = handle_quotes(com);
	if (!com)
		return (NULL);
	return (com);
}
