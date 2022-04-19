/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:10:09 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:10:09 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strlist	init_strlist(void)
{
	t_strlist	new_strlist;

	new_strlist.head = NULL;
	new_strlist.size = 0;
	new_strlist.strarr_value = NULL;
	new_strlist.current_path = NULL;
	return (new_strlist);
}

t_strlist	*new_strlist(void)
{
	t_strlist	*new_list;

	new_list = malloc(sizeof(t_strlist));
	if (!new_list)
		return (NULL);
	*new_list = init_strlist();
	return (new_list);
}

void	deinit_strlist(t_strlist *list)
{
	t_strlist_node	*next_node;

	if (list)
	{
		while (list->size--)
		{
			next_node = list->head->next;
			free(list->head->str);
			free(list->head);
			list->head = next_node;
		}
		list->head = NULL;
		free(list->strarr_value);
		free(list->current_path);
	}
}

void	*free_strlist(t_strlist *list)
{
	deinit_strlist(list);
	free(list);
	list = NULL;
	return (NULL);
}

t_strlist	*make_strlist_from_null_terminated_str_array(char **envp)
{
	t_strlist	*list;

	list = new_strlist();
	if (!list)
		return (NULL);
	if (envp)
	{
		while (*envp)
		{
			if (append_str_to_strlist(list, *envp) == -1)
			{
				free_strlist(list);
				return (NULL);
			}
			envp++;
		}
		update_strlist_strarr_value(list);
	}
	list->ret = 0;
	return (list);
}
