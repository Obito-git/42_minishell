/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:19:21 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:19:21 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//After execution head->next becomes the head
void	remove_node_from_strlist(t_strlist *list, t_strlist_node *node)
{
	t_strlist_node	*curr;
	size_t			size;

	if (list && node)
	{
		if (list->head && list->size > 0)
		{
			size = list->size;
			curr = list->head;
			while (curr != node && size--)
				curr = curr->next;
			if (size > 0)
			{
				if (curr == list->head)
					list->head = list->head->next;
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr->str);
				free(curr);
				list->size--;
				if (list->size == 0)
					list->head = NULL;
			}
		}
	}
}

void	remove_str_from_strlist(t_strlist *list, char *str)
{
	t_strlist_node	*curr;
	size_t			size;

	if (list && str)
	{
		if (list->head)
		{
			curr = list->head;
			size = list->size;
			while (size-- && ft_strcmp(curr->str, str))
				curr = list->head->next;
			if (size > 0)
			{
				curr->prev->next = curr->next;
				curr->next->prev = curr->prev;
				free(curr);
				list->size--;
			}
		}
	}
}
