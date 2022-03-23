#include "minishell.h"

bool is_pipe_redir(char c)
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
			c->pipe = true;
		else if (s[0] == '>')
			c->out_mode = OUT_REWRITE;
		else if (s[0] == '<')
			c->in_mode = IN_FILE;
		if (s[0] == '>' && s[1] == '>')
			c->out_mode = OUT_APPEND;
		if (s[0] == '<' && s[1] == '<')
			c->in_mode = IN_HEREDOC;
		s[0] = ' ';
		if (c->out_mode == OUT_APPEND || c->in_mode == IN_HEREDOC)
			s[1] = ' ';
	}
}

//changing inside/outside state of the quotes
void	set_quotes(char c, bool *q, bool *dq)
{
	if (c == '\'' && !*q)
		*q = true;
	else if (c == '\'' && *q)
		*q = false;
	if (c == '\"' && !*dq)
		*dq = true;
	else if (c == '\"' && *dq)
		*dq = false;
}

//main parsing function
t_command	*parse(char *user_input, t_strlist *env)
{
	char **com;
	t_command *head;
	int i = 0;

	com = (char **) malloc(sizeof(char *) * (ft_strlen(user_input) + 1)); //FIX SIZE
	if (!com)
		return (NULL);
	com = cut_all_commands(com, user_input, &i);
	com = ft_strtrim_array(com, " ");
	set_input_pattern(com);
	if (!com)
		return (NULL);
	head = get_commands_list(com, env);
	i = 0;
	while (com && com[i])
		free(com[i++]);
	free(com);
	return (head);
}
