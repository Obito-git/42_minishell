#include "../minishell.h"

/*
*	char *c is the command
*
*/
t_command	*command_init(char *c, t_bool p, char in, char out)
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
	res->pid = -2;
	if (!res->command)
	{
		free_commands(res);
		return (NULL);
	}
	return (res);
}

void	free_commands(t_command *c)
{
	t_command 	*tmp;
	int			i;

	if (c)
		free(c->tube);
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
