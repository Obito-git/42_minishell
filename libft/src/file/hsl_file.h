/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_file.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:51 by zsheep            #+#    #+#             */
/*   Updated: 2022/02/22 12:08:04 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HSL_FILE_H
# define HSL_FILE_H

# include "../str/hsl_str.h"
# include "../write/hsl_write.h"

/**
 * 		ft_filename.c	
 * 		return string contains filename from filepath
 * 		return null on error
 */
char	*ft_filename(const char *filepath);

/**
 *		ft_is_extension.c
 * 		return 1 when filepath match with extension
 * 		return 0 on wrong extension or if filename is only extension
 * 		dot '.' (or another custom) char must be included in extension
 */
int		ft_is_extension(const char *filepath, const char *extension);

#endif /* HSL_FILE_H */
