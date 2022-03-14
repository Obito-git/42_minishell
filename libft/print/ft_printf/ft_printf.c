/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:05:32 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:05:34 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

t_arg	*get_init_arg(void)
{
	t_arg	*ar;

	ar = (t_arg *) malloc(sizeof(t_arg));
	if (ar == NULL)
		return (NULL);
	ar->type = 'c';
	ar->isnull = 0;
	ar->content = NULL;
	return (ar);
}

void	arg_del(t_arg *ar)
{
	if (ar != NULL)
	{
		free(ar->content);
		free(ar);
	}
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	len;
	char	*cpy;

	cpy = ft_strdup(s);
	va_start(args, s);
	len = parse(&args, cpy);
	va_end(args);
	free(cpy);
	return (len);
}
