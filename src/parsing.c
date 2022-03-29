#include "minishell.h"

//Tries to find the command
char	*find_command(char **envp, t_command *c)
{
	char	**splited;
	int		i;
	char	*test_path;

	i = 0;
	if (access(c->command, X_OK) == 0)
		return (ft_strdup(c->command));
	if (!*envp || !ft_strlen(c->command))
		return (NULL);
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	splited = ft_split(*envp, ':');
	while (splited && splited[i++])
	{
		test_path = ft_str_threejoin(splited[i], "/", c->command);
		if (!test_path || access(test_path, X_OK) == 0)
			break ;
		free(test_path);
		test_path = NULL;
	}
	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	free(splited);
	return (test_path);
}

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
void	print_strarray(char **com)
{
	while (*com)
	{
		printf("%s\n", *com);
		com++;
	}
}

t_command	*parse(char *user_input, t_strlist *env)
{
	char **com;
	t_command *head;
	int i = 0;

	com = (char **) malloc(sizeof(char *) * (ft_strlen(user_input) + 2));
	if (!com)
		return (NULL);
	com = cut_all_commands(com, user_input, &i);
	com = ft_strtrim_array(com, " ");
	print_strarray(com);
	com = expand_args(com, env);
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
