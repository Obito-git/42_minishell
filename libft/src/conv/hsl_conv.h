/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_conv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:17:02 by zsheep            #+#    #+#             */
/*   Updated: 2022/02/01 12:17:02 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSL_CONV_H
# define HSL_CONV_H

# include <stdlib.h>
# include "../str/hsl_str.h"

/**
 *		ft_atoi_base.c
 */
int		ft_atoi_base(char *str, char *base);

/**
 *		ft_atoi.c
 */
int		ft_atoi(const char *str);

/**
 *		ft_atol_severe.c
 */
long	ft_atol_severe(const char *str);

/**
 *		ft_convert_base.c
 */
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

/**
 *		ft_itoabtw.c
 */
char	*ft_itoabtw(char *left_str, int nbr, char *right_str);

/**
 *		ft_itoa.c
 */
char	*ft_itoa(int n);

/**
 *		ft_nbrlen.c
 */
int		ft_nbrlen(long nbr, int base);

#endif /* HSL_CONV_H */
