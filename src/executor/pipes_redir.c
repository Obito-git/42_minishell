#include "../../minishell.h"

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

/*
* tube[0] → contiendra le fichier descripteur de l'extrémité de lecture
* tube[1] → contiendra le fichier descripteur de l'extrémité d'écriture
*/
void    set_tubes_path(t_command *c)
{
    if (c->pipe)
    {
        printf("out\n");
        dup2(c->tube[1], STDOUT_FILENO);
    }
    if (c->prev && c->prev->pipe)
    {
        printf("in\n");
        dup2(c->tube[0], STDIN_FILENO);
    }
    close(c->tube[0]);
    close(c->tube[1]);
}