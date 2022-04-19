/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:17:46 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:17:46 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node_to_strlist(t_strlist *list, t_strlist_node *node)
{
	if (list && node)
	{
		if (list->head)
		{
			node->prev = list->head->prev;
			node->next = list->head;
			list->head->prev->next = node;
			list->head->prev = node;
		}
		else
		{
			node->prev = node;
			node->next = node;
			list->head = node;
		}
		list->size++;
	}
}

int	append_str_to_strlist(t_strlist *list, char *str)
{
	t_strlist_node	*new_node;

	new_node = new_strlist_node();
	if (new_node == NULL)
		return (-1);
	new_node->str = ft_strdup(str);
	new_node->len = ft_strlen(str);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (-1);
	}
	append_node_to_strlist(list, new_node);
	return (0);
}

int	append_strarray_to_strlist(t_strlist *list, char **strarray)
{
	int	i;

	i = 0;
	while (strarray[i])
	{
		if (append_str_to_strlist(list, strarray[i]))
			return (-1);
		i++;
	}
	return (0);
}
