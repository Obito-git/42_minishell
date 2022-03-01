#include "../minishell.h"

/*
*	char *c is the command
*
*/
/*
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
	res->pipe = p;
	res->in_mode = in;
	res->out_mode = out;
	res->next = NULL;
	return (res);
}
*/
t_command	*command_init()
{
	t_command	*res;

	res = (t_command *) malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	res->pipe = 0;
	res->in_mode = 0;
	res->out_mode = 0;
	res->next = NULL;
	return (res);
}

void	free_command(t_command *c)
{
	t_command *tmp;

	if (!c)
		return ;
	while (c)
	{
		free(c->command);
		tmp = c->next;
		free(c);
		c = tmp;
	}
}
