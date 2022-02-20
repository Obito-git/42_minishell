/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_coffee.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:50:44 by sloquet           #+#    #+#             */
/*   Updated: 2022/01/29 21:15:37 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hsl_debug.h"

void	db(char *_FI, int _LN, char *debug_msg)
{
	ft_printf("\n\e[0;33m%s:%d: %s\e[0m\n", _FI, _LN, debug_msg);
	ft_printf("Paused...");
	getchar();
}

void	db3(char *_FI, int _LN, char *debug_msg)
{
	ft_printf("\n\e[0;35m%s\e[0;36m:\e[0;32m%d\e[0;36m:", _FI, _LN);
	ft_printf("\e[0;33m %s\e[2;36m\n", debug_msg);
	ft_putxnl(42, "-");
	dbg_cmd(_FI, _LN - 3, 0);
	dbg_cmd(_FI, _LN - 2, 0);
	dbg_cmd(_FI, _LN - 1, 0);
	dbg_cmd(_FI, _LN, 1);
	dbg_cmd(_FI, _LN + 1, 0);
	dbg_cmd(_FI, _LN + 2, 0);
	dbg_cmd(_FI, _LN + 3, 0);
	ft_putxnl(42, "-");
	ft_printf("\e[0;33mPaused...\e[0m");
	getchar();
}

void	dbx(char *_FI, int _LN, char *debug_msg, int range)
{
	int	i;

	ft_printf("\n\e[0;35m%s\e[0;36m:\e[0;32m%d\e[0;36m:", _FI, _LN);
	ft_printf("\e[0;33m %s\e[2;36m\n", debug_msg);
	ft_putxnl(42, "-");
	i = range;
	while (i > 0)
	{
		dbg_cmd(_FI, _LN - i, 0);
		i--;
	}
	dbg_cmd(_FI, _LN, 1);
	while (i < range)
	{
		dbg_cmd(_FI, _LN + i, 0);
		i++;
	}
	ft_putxnl(42, "-");
	ft_printf("\e[0;33mPaused...\e[0m");
	getchar();
}
