#include "minishell.h"

//close opened fds if possible and frees struct
void	close_fds(t_inout_fd *fds)
{
	if (!fds)
		return ;
	if (fds->in_fd != -1)
		close(fds->in_fd);
	if (fds->out_fd != -1)
		close(fds->out_fd);
	free(fds);
}

//opens file or create file with append or rewrite mode.
//returns file fd
// -1 will be returned if no need to open file, -2 in error case
int	set_out_path(t_command *c, int old_fd)
{
	int		fd;
	char	*err_msg;

	fd = -1;
	if (c->out_mode == OUT_APPEND)
		fd = open(c->next->command, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (c->out_mode == OUT_REWRITE)
		fd = open(c->next->command, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (c->out_mode && old_fd != -1)
		close(old_fd);
	if (c->out_mode && fd == -1)
	{
		err_msg = ft_strjoin(HEADER, c->next->command);
		if (!err_msg)
			perror(c->next->command);
		else
			perror(err_msg);
		free(err_msg);
		return (-2);
	}
	return (fd);
}

//opens file or calls heredoc mode and returns fd of it
// -1 will be returned if no need to open file, -2 in error case
int	set_in_path(t_command *head, t_command *c, int old_fd)
{
	int	fd;

	fd = -1;
	if (c->in_mode)
	{
		if (c->in_mode == IN_FILE)
			fd = open(c->next->command, O_RDONLY);
		else
			fd = get_heredoc_fd(c->next->command, head, c);
		if (old_fd != -1)
			close(old_fd);
		if (fd == -1)
		{
			perror(c->next->command);
			return (-2);
		}
		set_tubes_path(head, c->next);
	}
	return (fd);
}

/*	tries to open a file and redirect input or output using file descriptor.
*	supports multiple file rederections like:
*	cmd > file1 > file2 > file3
*	in this case file1, file2 and file3 will be created, STDOUT will be
*	replaced by file3 fd. File descriptors of file1 and file2 will be closed.
*/
t_inout_fd *set_redirections(t_command *c, t_command *head, t_strlist *env)
{
	t_inout_fd	*fds;

	fds = (t_inout_fd *) malloc(sizeof(t_inout_fd));
	if (!fds)
		return (NULL);
	fds->in_fd = -1;
	fds->out_fd = -1;
	while (c && (c->in_mode || c->out_mode))
	{
		fds->in_fd = set_in_path(head, c, fds->in_fd);
		fds->out_fd = set_out_path(c, fds->out_fd);
		if (fds->in_fd == -2 || fds->out_fd == -2)
		{
			close_fds(fds);
			free_commands(head);
			free_strlist(env);
			exit(EXIT_FAILURE);
		}
		c = c->next;
	}
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
void    set_tubes_path(t_command *head, t_command *c)
{
	if (c && c->pipe)
		dup2(c->tube[1], STDOUT_FILENO);
	if (c && c->prev && c->prev->pipe)
		dup2(c->prev->tube[0], STDIN_FILENO);
	close_extra_tubes(head, c);
}
