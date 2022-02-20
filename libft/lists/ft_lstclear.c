/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:03:35 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/24 09:03:41 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*previos;

	while (*lst)
	{
		previos = *lst;
		*lst = previos->next;
		(del)(previos->content);
		free(previos);
	}
	*lst = NULL;
}
