/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:13:15 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 09:12:21 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAX_FD 1024
# include "../../libft.h" 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_felement
{
	int					fd;
	int					is_read;
	char				*line;
	char				*buffer;
	char				*buf_temp;
}				t_felement;

t_felement	*init_elem(int fd);
char		*get_next_line(int fd);
char		*ft_join(char *from, char *to, size_t size);
char		*free_memory(t_felement *elem, char *tmp);

#endif
