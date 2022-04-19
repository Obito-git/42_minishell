/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_strlist_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:20:34 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:20:34 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_strlist_total_len(t_strlist strlist)
{
	int	total_len;

	total_len = 0;
	if (strlist.head)
	{
		while (strlist.size--)
		{
			total_len += strlist.head->len;
			strlist.head = strlist.head->next;
		}
	}
	return (total_len);
}

void	print_strlist(t_strlist list)
{
	while (list.size--)
	{
		printf("%s\n", list.head->str);
		list.head = list.head->next;
	}
}

void	strlistcat(char *dst, t_strlist *list)
{
	if (list->head)
	{
		ft_strcat_slice(dst, list->head->str, list->head->len);
		list->head = list->head->next;
	}
}
