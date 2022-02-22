/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_str.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:01:42 by zsheep            #+#    #+#             */
/*   Updated: 2022/02/22 12:01:42 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSL_STR_H
# define HSL_STR_H

# include <stdlib.h>
# include <unistd.h>

/**
 *		ft_arfree.c
 */
int		ft_arfree(char **array);

/**
 *		ft_split.c
 */
char	**ft_split(const char *s, char c);

/**
 *		ft_strchr.c
 */
char	*ft_strchr(const char *s, int c);

/**
 *		ft_strcmp.c
 */
int		ft_strcmp(char *s1, char *s2);

/**
 *		ft_strcpy.c
 */
char	*ft_strcpy(char *dest, const char *src);

/**
 *		ft_strdup.c
 */
char	*ft_strdup(const char *src);

/**
 *		ft_striteri.c
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 *		ft_strjoin.c
 */
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjointri(char const *s1, char const *s2, char const *s3);

/**
 *		ft_strlcat.c
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 *		ft_strlcpy.c
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 *		ft_strlen.c
 */
size_t	ft_strlen(const char *str);

/**
 *		ft_strmapi.c
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 *		ft_strncmp.c
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 *		ft_strnstr.c
 */
char	*ft_strnstr(const char *big, const char *sub, size_t len);

/**
 *		ft_strrchr.c
 */
char	*ft_strrchr(const char *s, int c);

/**
 *		ft_strtolower.c
 */
char	*ft_strtolower(char *str);

/**
 *		ft_strtoupper.c
 */
char	*ft_strtoupper(char *str);

/**
 *		ft_strtrim.c
 */
char	*ft_strtrim(const char *s1, const char *set);

/**
 *		ft_substr.c
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 *		get_next_line.c
 */
char	*get_next_line(int fd);

#endif /* HSL_STR_H */
