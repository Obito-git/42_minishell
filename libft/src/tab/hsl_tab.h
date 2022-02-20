/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_tab.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:30:21 by zsheep            #+#    #+#             */
/*   Updated: 2022/02/05 11:30:21 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSL_TAB_H
# define HSL_TAB_H

# include <stdlib.h>
# include "../write/hsl_write.h"
# include "../sort/hsl_sort.h"

/**
 *		ft_newtab.c
 */
int		*ft_newtab(int size);

/**
 *		ft_tab_are_distinct.c
 */
int		ft_tab_are_distinct(const int *tab, const int size);
int		ft_tab_uniq_count(const int *tab, const int size);

/**
 *		ft_tabdup.c
 */
int		*ft_tabdup(const int *tab, const int size);
int		*ft_tabdup_range(const int *tab, const int start, const int end);

/**
 *		ft_tab_firstquart.c
 */
int		ft_tab_firstquart(const int *tab, const int size);

/**
 *		ft_tab_issort.c
 */
int		ft_tab_issort_des(const int *tab, const int size);
int		ft_tab_issort_asc(const int *tab, const int size);

/**
 *		ft_tab_median.c
 */
int		ft_tab_median(const int *tab, const int size);
int		ft_tab_first_quar(const int *tab, const int size);
int		ft_tab_third_quar(const int *tab, const int size);

/**
 *		ft_tab_minmax.c
 */
int		ft_tab_min(const int *tab, const int size);
int		ft_tab_max(const int *tab, const int size);

/**
 *		ft_tabshow.c
 */
void	ft_tabshow(const int *tab, const int size, const char *name);

#endif /* HSL_TAB_H */
