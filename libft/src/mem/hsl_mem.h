/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_mem.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:17:03 by zsheep            #+#    #+#             */
/*   Updated: 2022/02/01 12:17:03 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSL_MEM_H
# define HSL_MEM_H

# include <stdlib.h>

/**
 *		ft_bzero.c
 */
void	ft_bzero(void *s, size_t n);

/**
 *		ft_calloc.c
 */
void	*ft_calloc(size_t num, size_t size);

/**
 *		ft_memchr.c
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 *		ft_memcmp.c
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 *		ft_memcpy.c
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 *		ft_memmove.c
 */
void	*ft_memmove(void *dst, const void *src, size_t n);

/**
 *		ft_memset.c
 */
void	*ft_memset(void *s, int c, size_t n);

#endif /* HSL_MEM_H */
