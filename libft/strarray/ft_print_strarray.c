/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_strarray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:44:01 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/07 15:44:01 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_print_strarray(char **com)
{
	if (com)
	{
		while (*com)
		{
			ft_printf("%s\n", *com);
			com++;
		}
	}
}
