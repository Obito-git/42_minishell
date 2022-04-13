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
#include "libft.h"
#include "ft_printf.h"
/*
int	ft_dprintf_str(int fd, const char *str, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, str);
	ret = ft_vdprintf_str(fd, str, ap);
	va_end(ap);
	return (ret);
}
*/

int	ft_dprintf_str(int fd, const char *str, ...)
{
	va_list	args;
	size_t	len;
	char	*cpy;

	cpy = ft_strdup(str);
	va_start(args, str);
	len = parse_and_execute_printf(fd, &args, cpy);
	va_end(args);
	free(cpy);
	return (len);
}
