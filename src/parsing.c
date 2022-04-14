#include "minishell.h"

/*
*	Modifies [< 'input file' 'command'] to ['command' < 'input file']
*	Used to execute 2 patterns by the same executor function
*/
void	set_input_pattern(char **s)
{
	char	*filename;
	char	*redir;
	size_t	i;

	i = 0;
	if (!s || !s[0] || !s[1] || !s[2])
		return ;
	if (!ft_strcmp(s[0], "<") || !ft_strcmp(s[0], "<<"))
	{
		redir = s[0];
		filename = s[1];
		while (s[i + 2] && (ft_strcmp(s[i + 2], "|")
				&& ft_strcmp(s[i + 2], ">") && ft_strcmp(s[i + 2], ">>")))
		{
			s[i] = s[i + 2];
			i++;
		}
		i = 0;
		while(s[i] && (ft_strcmp(s[i], "|")
				&& ft_strcmp(s[i], ">") && ft_strcmp(s[i], ">>")))
			i++;
		s[i - 2] = redir;
		s[i - 1] = filename;
	}
}

int	check_pathname_access(t_command *c)
{
	char	*msg;
	int		ret;

	ret = 0;
	msg = ft_strjoin(HEADER, c->command);
	if (!c->path_to_bin && (!ft_strncmp("./", c->command, 2)
		|| ft_strchr(c->command, '/')))
	{
		if ((access(c->command, X_OK) == -1 || access(c->command, F_OK) == -1)
			&& !isDirectory(c->command))
			perror(msg);
		else if (isDirectory(c->command) || contains_only(c->command, '/'))
			ft_dprintf_str(2, "%s%s: is a directory\n", HEADER, c->command);
		if ((access(c->command, F_OK) == 0 && access(c->command, X_OK) == -1)
			|| isDirectory(c->command) || contains_only(c->command, '/'))
			ret = 126;
		else if (access(c->command, F_OK) == -1)
			ret = 127;
		else
			c->path_to_bin = ft_strdup(c->command);
	}
	free(msg);
	return (ret);
}

//Tries to find the command
char	*find_command(char **envp, t_command *c)
{
	char	**splited;
	int		i;
	char	*test_path;

	i = 0;
	if (!ft_strncmp("./", c->command, 2) || ft_strchr(c->command, '/'))
		return (NULL);
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp || !ft_strlen(c->command))
		return (NULL);
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

bool	is_pipe_redir_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_command	*parse(char *user_input, t_strlist *env)
{
	t_command	*head;
	t_strlist	*list;

	list = expand_pipeline(user_input, env);
	if (!list)
		return (NULL);
	if (!list->head)
	{
		free(list);
		return (NULL);
	}
	update_strlist_strarr_value(list);
	set_input_pattern(list->strarr_value);
	head = get_commands_list(list->strarr_value, env);
	free_strlist(list);
	return (head);
	//Where is user_input freed ?
}
