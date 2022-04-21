/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:37:43 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:37:43 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//tries to delete heredoc tmpfile
void	delete_tmpfiles(t_command *head)
{
	char		*filename;
	t_command	*tmp_cmd;
	t_redir		*tmp_red;

	if (head)
	{
		tmp_cmd = head;
		while (tmp_cmd)
		{
			tmp_red = tmp_cmd->infile;
			while (tmp_red)
			{
				if (tmp_red->mode == IN_HEREDOC)
				{
					filename = get_heredoc_tmpname(head, tmp_cmd, tmp_red);
					if (filename)
						unlink(filename);
					free(filename);
				}
				tmp_red = tmp_red->next;
			}
			tmp_cmd = tmp_cmd->next;
		}
	}
}

char	*read_heredoc_mode_lopped(char *s, char *delim)
{
	char	*current_line;
	char	*tmp;
	int		i;

	i = 2;
	while (s)
	{
		current_line = readline("> ");
		tmp = ft_strjoin(s, "\n");
		free(s);
		if (!current_line || !ft_strcmp(current_line, delim))
		{
			if (!current_line)
				ft_dprintf_str(2, ERROR_HEREDOC1 ERROR_HEREDOC2, i, delim);
			free(current_line);
			return (tmp);
		}
		s = ft_strjoin(tmp, current_line);
		free(current_line);
		free(tmp);
		i++;
	}
	return (s);
}

//heredoc readline funtion.
char	*read_heredoc_mode(char *delim)
{
	char	*first_line;

	first_line = readline("> ");
	if (!first_line || !ft_strcmp(first_line, delim))
	{
		if (!first_line)
			ft_dprintf_str(2, ERROR_HEREDOC1 ERROR_HEREDOC2, 1, delim);
		free(first_line);
		return (NULL);
	}
	return (read_heredoc_mode_lopped(first_line, delim));
}

/*Generate name for tmp file depending on the position of the structure in the
 * list*/
char	*get_heredoc_tmpname(t_command *head,
		t_command *current, t_redir *redir)
{
	t_redir	*r;
	char	*filename;
	char	*numb;
	char	*tmp;
	int		id;

	id = 0;
	filename = ft_strdup(".tmpheredoc");
	while (head && head != current)
	{
		id++;
		head = head->next;
	}
	r = current->infile;
	while (r && r != redir)
	{
		id += 10;
		r = r->next;
	}
	tmp = filename;
	numb = ft_itoa(id);
	filename = ft_strjoin(filename, numb);
	free(tmp);
	free(numb);
	return (filename);
}

/*Reads content in heredoc mode and saves it in hidden tmp file.*/
int	get_heredoc_fd(char *delim, t_command *head,
					t_command *current, t_redir *red)
{
	char	*content;
	char	*filename;
	int		fd;

	content = read_heredoc_mode(delim);
	filename = get_heredoc_tmpname(head, current, red);
	if (!filename)
	{
		free(content);
		return (0);
	}
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(fd, content, ft_strlen(content));
	close(fd);
	fd = open(filename, O_RDONLY);
	free(content);
	free(filename);
	return (fd);
}
