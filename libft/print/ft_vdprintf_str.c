/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:11:38 by tpouget           #+#    #+#             */
/*   Updated: 2022/03/22 14:11:38 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	write_format(int fd, const char **str, va_list ap)
{
	int		written;
	char	*charstr;

	written = 0;
	if (**str == '%' && *(*str + 1) == 's')
	{
		charstr = va_arg(ap, char *);
		if (charstr == NULL)
			written = write(fd, "(null)", sizeof("(null)") - 1);
		else
			written = write(fd, charstr, ft_strlen(charstr));
		(*str) += 2;
	}
	else if (**str == '%')
	{
		written = write(fd, "%", 1);
		(*str) += 1;
	}
	return (written);
}

int	ft_vdprintf_str(int fd, const char *str, va_list ap)
{
	int			total_written;
	const char	*behind;

	total_written = 0;
	behind = str;
	while (*str)
	{
		while (*str && *str != '%')
		{
			str++;
		}
		total_written += write(fd, behind, str - behind);
		total_written += write_format(fd, &str, ap);
		behind = str;
	}
	return (total_written);
}
