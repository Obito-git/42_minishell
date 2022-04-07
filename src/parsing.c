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

bool	is_pipe_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	**expand_simple_command(char *simple_command, t_strlist *env)
{
	char	**com;
	char	*expanded;

	com = quote_preserving_split(simple_command);
	if (!com)
		return (NULL);
	com = expand_args(com, env);
	if (!com)
		return (NULL);
	expanded = ft_join_null_terminated_str_array(com);
	free_strarray(com);
	if (!expanded)
		return (NULL);
	com = split_on_unquoted_whitespace(expanded, " \t");
	free(expanded);
	if (!com)
		return (NULL);
	com = handle_quotes(com);
	if (!com)
		return (NULL);
	return (com);
}

//Expansion covers quote handling and variable replacement
t_strlist	*expand_pipeline(char *user_input, t_strlist *env)
{
	char		**pipeline;
	char		**simple_cmd;
	int			i;
	t_strlist	*arg_list;

	arg_list = new_strlist();
	if (!arg_list)
		return (NULL);
	pipeline = split_on_unquoted_redir(user_input, ">|<");
	i = 0;
	while (pipeline && pipeline[i])
	{
		simple_cmd = expand_simple_command(pipeline[i], env);
		if (!simple_cmd || append_strarray_to_strlist(arg_list, simple_cmd))
		{
			free_strarray(pipeline);
			free_strlist(arg_list);
			return (NULL);
		}
		free_strarray(simple_cmd);
		i++;
	}
	free_strarray(pipeline);
	return (arg_list);
}

t_command	*parse(char *user_input, t_strlist *env)
{
	t_command	*head;
	t_strlist	*list;

	list = expand_pipeline(user_input, env);
	if (!list) //prot !list->head, list free
		return (NULL);
	if (!list->head)
	{
		free(list);
		return (NULL);
	}
	update_strlist_strarr_value(list);
	head = get_commands_list(list->strarr_value, env);
	free_strlist(list);
	return (head);
	//Where is user_input freed ?
}
