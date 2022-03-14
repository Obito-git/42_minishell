/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:05:26 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/24 09:05:39 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*act;

	if (!lst)
		return (0);
	i = 1;
	act = lst->next;
	while (act != NULL)
	{
		act = act->next;
		i++;
	}
	return (i);
}
