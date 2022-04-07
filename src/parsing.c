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

t_command	*parse(char *user_input, t_strlist *env)
{
	t_command	*head;
	t_strlist	*list;

	list = expand_pipeline(user_input, env);
	if (!list || !list->head) //prot !list->head, list free
		return (NULL);
	update_strlist_strarr_value(list);
	head = get_commands_list(list->strarr_value, env);
	free_strlist(list);
	return (head);
	//Where is user_input freed ?
}
