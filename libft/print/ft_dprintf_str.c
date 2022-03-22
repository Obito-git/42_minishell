/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:11:26 by tpouget           #+#    #+#             */
/*   Updated: 2022/03/22 14:11:26 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "../libft.h"

int	ft_dprintf_str(int fd, const char *str, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, str);
	ret = ft_vdprintf_str(fd, str, ap);
	va_end(ap);
	return (ret);
}
