/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:11:33 by tpouget           #+#    #+#             */
/*   Updated: 2022/03/22 14:11:33 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

int	ft_printf_str(const char *str, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, str);
	ret = ft_vdprintf_str(STDOUT_FILENO, str, ap);
	va_end(ap);
	return (ret);
}
