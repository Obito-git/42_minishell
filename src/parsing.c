#include "minishell.h"

t_bool is_pipe_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* checks whether the symbol is a pipe or a redirect and 
*  sets the corresponding value of the structure variable.
*  Replaces the character with a space
*/
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
t_command	*parse(char *user_input)
{
	char **com;
	t_command *head;
	int i = 0;

	com = (char **) malloc(sizeof(char *) * (ft_strlen(user_input) + 1)); //FIX SIZE
	if (!com)
		return (NULL);
	com = cut_all_commands(com, user_input, &i);
	com = ft_strtrim_array(com, " ");
	if (!com)
		return (NULL);
	head = get_commands_list(com);
	i = 0;
	while (com && com[i])
		free(com[i++]);
	free(com);
	return (head);
}
