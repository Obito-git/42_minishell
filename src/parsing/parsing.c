#include "../../minishell.h"


t_bool is_pipe_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	set_command_redir(t_command *c, char *s)
{
	if (is_pipe_redir(s[0]))
	{
		if (s[0] == '|')
			c->pipe = TRUE;
		else if (s[0] == '>')
			c->out_mode = OUT_REWRITE;
		else if (s[0] == '<')
			c->in_mode = IN_SOLO;
		if (s[0] == '>' && s[1] == '>')
			c->out_mode = OUT_APPEND;
		if (s[0] == '<' && s[1] == '<')
			c->out_mode = IN_MULT;
		s[0] = ' ';
		if (c->out_mode == OUT_APPEND || c->in_mode == IN_MULT)
			s[1] = ' ';
	}
}

//changing inside/outside state of the quotes
void	set_quotes(char c, t_bool *q, t_bool *dq)
{
	if (c == '\'' && !*q)
		*q = TRUE;
	else if (c == '\'' && *q)
		*q = FALSE;
	if (c == '\"' && !*dq)
		*dq = TRUE;
	else if (c == '\"' && *dq)
		*dq = FALSE;
}

//main parsing function
t_command	**parse(char *com)
{
	char **commands;
	t_command **res;
	int i = 0;

	commands = cut_all_commands(com, &i);
	i = 0;
	if (!commands)
		printf("Commands == NULL\n"); //FIXME
	commands = ft_strtrim_array(commands, " ");
	if (!commands)
		printf("Trim == NULL\n"); //FIXME
	res = get_commands_arr(commands);
	while (commands && commands[i])
		free(commands[i++]);
	free(commands);
	return (res);
}
