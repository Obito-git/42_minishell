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
	if (!res->command)
	{
		free(res);
		return (NULL);
	}
	res->args = NULL;
	res->pipe = p;
	res->in_mode = in;
	res->out_mode = out;
	res->next = NULL;
	return (res);
}

void	free_commands(t_command *c)
{
	t_command 	*tmp;
	int			i;

	if (!c)
		return ;
	while (c)
	{
		i = 0;
		free(c->command);
		while (c->args[i])
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
