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

//applies free on each element of an array list
void	free_commands(t_command *c)
{
	t_command 	*tmp;
	int			i;

	if (c)
		free(c->tube); //find solution with tubes closing
	while (c)
	{
		free(c->command);
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

t_command	*get_last_cmd(t_command *head)
{
	t_command	*tmp;

	tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}