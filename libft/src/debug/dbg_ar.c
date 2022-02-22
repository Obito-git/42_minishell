/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_ar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:55:18 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/22 11:55:32 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_debug.h"

void	dbg_ar(const char **array, const char *name)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		ft_printf("%s[%d]: %s\n", name, i, array[i]);
		i++;
	}
}
