#include "minishell.h"

/*
*	used for the initialision of t_command structure with default values
*/
t_command	*command_init(char *c, bool p, char in, char out)
{
	t_command	*res;

	res = (t_command *) malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	res->command = ft_strdup(c);
	res->path_to_bin = NULL;
	res->tube = NULL;
	res->args = NULL;
	res->pipe = p;
	res->in_mode = in;
	res->out_mode = out;
	res->next = NULL;
	res->prev = NULL;
	if (!res->command)
	{
		free_commands(res);
		return (NULL);
	}
	return (res);
}

//tries to delete heredoc tmpfile
void	delete_tmpfiles(t_command *head)
{
	char		*filename;
	t_command	*tmp;

	if (head)
	{
		tmp = head;
		while (tmp)
		{
			if (tmp->in_mode == IN_HEREDOC)
			{
				filename = get_heredoc_tmpname(head, tmp);
				if (filename)
					unlink(filename);
				free(filename);
			}
			tmp = tmp->next;
		}
	}
}

//applies free on each element of an array list
t_command	*free_commands(t_command *c)
{
	t_command 	*tmp;
	int			i;

	delete_tmpfiles(c);
	if (c)
	{
		while (c)
		{
			free(c->command);
			free(c->path_to_bin);
			free(c->tube);
			i = 0;
			while (c->args && c->args[i])
			{
				free(c->args[i]);
				i++;
			}
			free(c->args);
			tmp = c->next;
			free(c);
			c = tmp;
		}
	}
	return (NULL);
}

t_command	*get_last_cmd(t_command *head)
{
	t_command	*tmp;

	tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}
