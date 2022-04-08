/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*_next_any_quote(char *str)
{
	while (*str && !ft_is_in_set(*str, "\'\""))
		str++;
	return (str);
}

static char	_set_quote_mode(char c)
{
	char	quote;

	if (c == '\'' || c == '\"')
		quote = c;
	else
		quote = 0;
	return (quote);
}

int	check_quotes(char *str)
{
	char	quote;

	quote = _set_quote_mode(*str);
	while (*str)
	{
		if (quote == 0)
		{
			str = _next_any_quote(str);
			quote = *str;
		}
		else
		{
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == 0)
				return (-1);
			else
				quote = 0;
			str++;
		}
	}
	return (0);
}
