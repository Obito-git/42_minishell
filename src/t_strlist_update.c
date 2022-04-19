/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:20:09 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:20:09 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_strlist_strarr_value(t_strlist *list)
{
	t_strlist	tmp_list;
	char		**new_strarr_val;

	tmp_list = *list;
	new_strarr_val = malloc((list->size + 1) * sizeof(char **));
	if (!new_strarr_val)
		return (-1);
	free(list->strarr_value);
	list->strarr_value = new_strarr_val;
	while (tmp_list.size--)
	{
		*new_strarr_val = tmp_list.head->str;
		tmp_list.head = tmp_list.head->next;
		new_strarr_val++;
	}
	*new_strarr_val = NULL;
	return (0);
}
