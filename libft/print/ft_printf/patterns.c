/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_pattern.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:28:58 by amyroshn          #+#    #+#             */
/*   Updated: 2021/12/06 15:29:05 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

size_t	d_pattern(t_arg *ar)
{
	size_t	len;

	ft_putnbr_fd(*(long *)ar->content, 1);
	len = ft_numblen(*(long *)ar->content);
	arg_del(ar);
	return (len);
}

size_t	p_pattern(t_arg *ar)
{
	unsigned long	cont;
	size_t			len;
	char			*base;
	char			*res;

	cont = (*(unsigned long *) ar->content);
	base = "0123456789abcdef";
	if (cont == 0)
	{
		ft_putstr("0x0");
		len = 3;
	}
	else
	{
		ft_putstr("0x");
		res = ft_convert_base(cont, base);
		if (!res)
			return (0);
		ft_putstr(res);
		len = ft_strlen(res) + 2;
		free(res);
	}
	arg_del(ar);
	return (len);
}

size_t	s_pattern(t_arg *ar)
{
	size_t	len;

	if (ar->type == 'c')
	{
		ft_putchar((char) *(int *)ar->content);
		arg_del(ar);
		return (1);
	}
	if ((char *)ar->content == NULL)
	{
		ft_putstr("(null)");
		len = 6;
	}
	else
	{
		ft_putstr((char *)ar->content);
		len = ft_strlen((char *)ar->content);
	}
	arg_del(ar);
	return (len);
}

size_t	u_pattern(t_arg *ar)
{
	unsigned int	n;
	size_t			len;

	n = *(unsigned int *) ar->content;
	ft_putnbr(n);
	len = ft_numblen(n);
	arg_del(ar);
	return (len);
}

size_t	xx_pattern(t_arg *ar)
{
	unsigned int	cont;
	size_t			len;
	char			*base;
	char			*res;

	cont = (*(unsigned int *) ar->content);
	if (ar->type == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	res = ft_convert_base(cont, base);
	ft_putstr(res);
	len = ft_strlen(res);
	free(res);
	arg_del(ar);
	return (len);
}
