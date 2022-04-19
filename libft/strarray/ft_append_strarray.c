/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_strarray.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 13:06:44 by amyroshn          #+#    #+#             */
/*   Updated: 2021/11/24 09:06:49 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	**ft_append_strarray(char **arr, char *str)
{
	char	**new_arr;
	size_t	i;

	i = 0;
	new_arr = ft_cpy_strarray(arr);
	free_strarray(arr);
	if (!new_arr)
	{
		new_arr = (char **) malloc(sizeof(char *) * (2));
		if (new_arr)
		{
			new_arr[0] = NULL;
			new_arr[1] = NULL;
		}
	}
	if (!new_arr)
		return (NULL);
	while (new_arr[i])
		i++;
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (free_strarray(new_arr));
	new_arr[i + 1] = NULL;
	return (new_arr);
}
