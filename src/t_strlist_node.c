/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:18:50 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:18:50 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_strlist_node	init_strlist_node(void)
{
	t_strlist_node	node;

	node.str = NULL;
	node.len = 0;
	node.prev = NULL;
	node.next = NULL;
	return (node);
}

t_strlist_node	*new_strlist_node(void)
{
	t_strlist_node	*new_node;

	new_node = malloc(sizeof(t_strlist_node));
	if (!new_node)
		return (NULL);
	*new_node = init_strlist_node();
	return (new_node);
}
