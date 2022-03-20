#include "minishell.h"

//open file or create file with append or rewrite mode.
//if file is opened changing stdout to file fd
int	set_out_path(t_command *c)
{
	int	fd;

	fd = -1;
	if (c->out_mode)
	{
		if (c->out_mode == OUT_APPEND)
			fd = open(c->next->command, O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (c->out_mode == OUT_REWRITE)
			fd = open(c->next->command, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(c->next->command);
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
	}
	return (fd);
}

int	set_in_path(t_command *head, t_command *c)
{
	//FIXME if c->next not existing case
	int	fd;

	fd = -1;
	if (c->in_mode)
	{
		if (c->in_mode == IN_FILE)
			fd = open(c->next->command, O_RDONLY);
		else
			fd = get_heredoc_fd(c->next->command, head, c);
		if (fd == -1)
		{
			perror(c->next->command);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		set_tubes_path(head, c->next);
	}
	return (fd);
}

/*
* tube[0] → contiendra le fichier descripteur de l'extrémité de lecture
* tube[1] → contiendra le fichier descripteur de l'extrémité d'écriture
*/
void    set_tubes_path(t_command *head, t_command *c)
{
	if (c->pipe)
		dup2(c->tube[1], STDOUT_FILENO);
    if (c->prev && c->prev->pipe)
        dup2(c->prev->tube[0], STDIN_FILENO);
    close_extra_tubes(head, c);
}
