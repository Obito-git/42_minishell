/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:15:56 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:12:58 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_nlpos(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

char	*check_buffer(t_felement *elem, int nl_index)
{
	char	*tmp;

	tmp = NULL;
	if (!elem->buffer)
		return (NULL);
	if (nl_index >= 0)
	{
		tmp = ft_strdup(&elem->buffer[nl_index + 1]);
		elem->buffer[nl_index + 1] = 0;
		elem->line = ft_strdup(elem->buffer);
		if (!tmp || !elem->line)
			return (free_memory(elem, tmp));
		free(elem->buffer);
		elem->buffer = NULL;
		if (ft_strlen(tmp) == 0)
			free(tmp);
		else
			elem->buffer = tmp;
	}
	else
	{
		elem->line = elem->buffer;
		elem->buffer = NULL;
	}
	return (elem->line);
}

char	*read_bfrsep(t_felement *elem)
{
	int		read_bytecount;
	int		nl_index;

	elem->buf_temp = (char *) malloc(BUFFER_SIZE + 1);
	if (!elem->buf_temp)
		return (free_memory(elem, NULL));
	elem->line = NULL;
	nl_index = get_nlpos(elem->buffer);
	read_bytecount = 0;
	while (nl_index < 0)
	{
		read_bytecount = read(elem->fd, elem->buf_temp, BUFFER_SIZE);
		if (read_bytecount < 1)
			break ;
		if (!elem->buffer)
			elem->buffer = ft_strdup("");
		elem->buf_temp[read_bytecount] = 0;
		elem->buffer = ft_join(elem->buffer, elem->buf_temp, BUFFER_SIZE);
		nl_index = get_nlpos(elem->buf_temp);
		if (!elem->buffer)
			return (free_memory(elem, NULL));
	}
	if (read_bytecount < 1)
		elem->is_read = 1;
	return (check_buffer(elem, get_nlpos(elem->buffer)));
}

char	*get_next_line(int fd)
{
	static t_felement	*elem_arr[MAX_FD + 1];
	char				*res;

	if (fd < 0 || fd > MAX_FD)
		return (NULL);
	if (!elem_arr[fd])
		elem_arr[fd] = init_elem(fd);
	read_bfrsep(elem_arr[fd]);
	free(elem_arr[fd]->buf_temp);
	elem_arr[fd]->buf_temp = NULL;
	if ((elem_arr[fd]->line) || (!elem_arr[fd]->is_read
			&& elem_arr[fd]->buffer))
		return (elem_arr[fd]->line);
	res = ft_strdup(elem_arr[fd]->line);
	free_memory(elem_arr[fd], NULL);
	free(elem_arr[fd]);
	elem_arr[fd] = NULL;
	return (res);
}
