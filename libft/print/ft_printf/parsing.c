/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:32:05 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 12:53:23 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ispattern(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd'
		|| c == 'i' || c == 'u' || c == 'x' || c == 'X');
}

static size_t	find_pattern(t_arg	*ar)
{
	if (ar->type == 'd' || ar->type == 'i')
		return (d_pattern(ar));
	if (ar->type == 's' || ar->type == 'c')
		return (s_pattern(ar));
	if (ar->type == 'p')
		return (p_pattern(ar));
	if (ar->type == 'u')
		return (u_pattern(ar));
	if (ar->type == 'x' || ar->type == 'X')
		return (xx_pattern(ar));
	return (0);
}

size_t	print_pattern(char type, void *var_content)
{
	t_arg	*ar;

	ar = get_init_arg();
	if (ar == NULL)
		return (0);
	ar->type = type;
	ar->content = var_content;
	return (find_pattern(ar));
}

void	*parse_content(va_list *ar, char type)
{
	long			*i;
	unsigned long	*z;

	if (ar == NULL)
		return (NULL);
	if (type == 'd' || type == 'c' || type == 'i')
	{
		i = (long *) malloc(sizeof(long));
		*i = va_arg(*ar, int);
		return ((void *) i);
	}
	if (type == 's')
		return ((void *)ft_strdup(va_arg(*ar, char *)));
	if (type == 'p' || type == 'u' || type == 'x' || type == 'X')
	{
		z = (unsigned long *) malloc(sizeof(unsigned long));
		if (type == 'p')
			*z = va_arg(*ar, unsigned long);
		else
			*z = va_arg(*ar, unsigned int);
		return ((void *) z);
	}
	return (NULL);
}

size_t	parse(va_list	*ar, char *str)
{
	size_t	i;
	size_t	printed_chars;

	i = 0;
	printed_chars = 0;
	while (str[i])
	{
		if (str[i] == '%' && ispattern(str[i + 1]))
		{
			printed_chars += print_pattern(str[i + 1],
					parse_content(ar, str[i + 1]));
			i += 2;
			continue ;
		}
		if (str[i] == '%' && str[i + 1] == '%')
			i++;
		ft_putchar(str[i]);
		printed_chars++;
		i++;
	}
	return (printed_chars);
}
