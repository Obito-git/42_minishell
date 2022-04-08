/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:17 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/08 13:23:17 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	is_special_var_start_char(int c)
{
	if (c == '?'
		/*|| c == '$'*/
		/*|| c == '@'*/
		/*|| c == '#'*/
		/*|| c == '!'*/
		/*|| c == '-'*/
		/*|| c == '*'*/
		/*|| c == '_'*/
		/*|| ft_isdigit(c)*/
	)
		return (true);
	return (false);
}

bool	is_valid_shellvar_start_char(int c)
{
	if (ft_isdigit(c))
		return (false);
	if (is_special_var_start_char(c) || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_valid_env_var_char(int c)
{
	if (c == '_' || ft_isalpha(c))
		return (true);
	return (false);
}

bool	is_single_dollar(char *c)
{
	if (c[0] == '$')
		if (!is_valid_shellvar_start_char(c[1]))
			return (true);
	return (false);
}
