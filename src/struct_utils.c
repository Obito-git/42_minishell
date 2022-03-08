#include "../minishell.h"

/*
*	char *c is the command
*
*/
t_command	*command_init(char *c, t_bool p, char in, char out)
{
	t_command	*res;
	int			pipe_result;

	pipe_result = 0;
	res = (t_command *) malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	res->command = ft_strdup(c);
	res->tube = (int *) malloc(sizeof(int) * 2);
	if (res->tube)
		pipe_result = pipe(res->tube);
	res->args = NULL;
	res->pipe = p;
	res->in_mode = in;
	res->out_mode = out;
	res->next = NULL;
	if (!res->command || !res->tube || pipe_result != 0)
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

	while (c)
	{
		free(c->command);
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
