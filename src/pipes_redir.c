/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:06:21 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 15:06:21 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//opens file or create file with append or rewrite mode.
//returns file fd
// -1 will be returned if no need to open file, -2 in error case
int	set_out_path(t_command *c)
{
	int		fd;
	t_redir	*tmp;

	fd = -1;
	tmp = c->outfile;
	while (tmp)
	{
		if (fd != -1)
			close(fd);
		if (tmp->mode == OUT_APPEND)
			fd = open(tmp->filename, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (tmp->mode == OUT_REWRITE)
			fd = open(tmp->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_dprintf_str(2, "%s", HEADER);
			perror(tmp->filename);
			return (-2);
		}
		tmp = tmp->next;
	}
	return (fd);
}

//opens file or calls heredoc mode and returns fd of it
// -1 will be returned if no need to open file, -2 in error case
int	set_in_path(t_command *c)
{
	int		fd;
	t_redir	*tmp;

	fd = -1;
	tmp = c->infile;
	while (tmp)
	{
		if (fd != -1)
			close(fd);
		if (tmp->mode == IN_FILE)
			fd = open(tmp->filename, O_RDONLY);
		else
			fd = tmp->heredoc_fd;
		if (fd == -1)
		{
			ft_dprintf_str(2, "%s", HEADER);
			perror(tmp->filename);
			return (-2);
		}
		tmp = tmp->next;
	}
	return (fd);
}

/*	tries to open a file and redirect input or output using file descriptor.
*	supports multiple file rederections like:
*	cmd > file1 > file2 > file3
*	in this case file1, file2 and file3 will be created, STDOUT will be
*	replaced by file3 fd. File descriptors of file1 and file2 will be closed.
*/
t_inout_fd	*set_redirections(t_command *c)
{
	t_inout_fd	*fds;

	fds = (t_inout_fd *) malloc(sizeof(t_inout_fd));
	if (!fds)
		return (NULL);
	fds->in_fd = -1;
	fds->out_fd = -1;
	fds->in_fd = set_in_path(c);
	fds->out_fd = set_out_path(c);
	if (fds->in_fd == -2 || fds->out_fd == -2)
	{
		close_fds(fds);
		return (NULL);
	}
	fds->backup_in = dup(STDIN_FILENO);
	fds->backup_out = dup(STDOUT_FILENO);
	if (fds->out_fd != -1)
		dup2(fds->out_fd, STDOUT_FILENO);
	if (fds->in_fd != -1)
		dup2(fds->in_fd, STDIN_FILENO);
	return (fds);
}

/*
* tube[0] → contiendra le fichier descripteur de l'extrémité de lecture
* tube[1] → contiendra le fichier descripteur de l'extrémité d'écriture
*/
void	set_tubes_path(t_command *head, t_command *c)
{
	if (c && c->pipe)
		dup2(c->tube[1], STDOUT_FILENO);
	if (c && c->prev && c->prev->pipe)
		dup2(c->prev->tube[0], STDIN_FILENO);
	close_extra_tubes(head, NULL);
}
