#include "minishell.h"

//returns args (array of strings) deleting multiple spaces and external quotes
/*
char	**parse_command_args(char *command)
{
	char	**res;
	int		i;
	int		size;

	i = 0;
	size = 1;
	res = NULL;
	if (ft_strlen(command) == 0)
	{
		res = (char **) malloc(sizeof(char *) * 2);
		if (!res)
			return (NULL);
		res[0] = NULL;
		return (res);
	}
	while (command[i])
	{
		if (i > 0 && command[i] == ' ' && command[i - 1] != ' ')
			size++;
		i++;
	}
	res = ft_minishell_split(res, command, size, i);
	return (res);
}

//set redir/pipe value inside struct and delete character from the string
void	set_command_args(t_command *c, char *s, int y)
{
	bool	inside_quotes;
	bool	inside_double_quotes;
	char	*tmp;

	inside_quotes = false;
	inside_double_quotes = false;
	if (!c || !s)
		return ;
	while(s[y])
	{
		set_quotes(s[y], &inside_quotes, &inside_double_quotes);
		if (!inside_quotes && !inside_double_quotes && is_pipe_redir(s[y]))
			break ;
		y++;
	}
	set_command_redir(c, &s[y]);
	tmp = ft_strtrim(s, " ");
	if (!tmp)
		return ;
	c->args = parse_command_args(tmp);
	free(tmp);
} */

char	**get_com_args(char **c, int *pos)
{
	int		y;
	char	**args;

	y = 0;
	while (c[*pos + y] && !is_pipe_redir(c[*pos + y][0]))
		y++;
	args = (char **) malloc(sizeof(char *) * (y + 2));
	if (!args)
		return (NULL);
	y = 0;
	while (c[*pos] && !is_pipe_redir(c[*pos][0]))
	{
		args[y] = ft_strdup(c[*pos]);
		if (!args[y++])
		{
			y = 0;
			while (args[y])
				free(args[y++]);
			free(args);
			return (NULL);
		}
		*pos += 1;
	}
	args[y] = NULL;
	return (args);
}

void	set_struct_pipes_redirections(t_command *com, char *c)
{
	if (!c)
		return ;
	if (!ft_strcmp(c, "|"))
		com->pipe =true;
	else
	{
		if (!ft_strcmp(c, ">>"))
			com->out_mode = OUT_APPEND;
		else if (!ft_strcmp(c, ">"))
			com->out_mode = OUT_REWRITE;
		else if (!ft_strcmp(c, "<"))
			com->in_mode = IN_FILE;
		else if (!ft_strcmp(c, "<<"))
			com->in_mode = IN_HEREDOC;
		else
			printf("UNKNOWN DELEMITER\n");
	}
}

//return parsed struct
t_command *get_command(char **c, int *pos, t_strlist *env)
{
	t_command	*res;

	res = command_init();
	if (!res)
		return (NULL);
	res->command = ft_strdup(c[*pos]);
	if (!res->command)
		return (NULL);
	res->args = get_com_args(c, pos);
	if (!res->args)
	{
		free(res->command);
		free(res);
		return (NULL);
	}
	set_struct_pipes_redirections(res, c[*pos]);
	res->path_to_bin = find_command(env->strarr_value, res);
	if (c[*pos])
		*pos += 1;
	return (res);
}

t_command	*set_command_list_tube(t_command *head)
{
	int			*tube;
	t_command	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->pipe)
		{
			tube = (int *) malloc(sizeof(int) * 2);
			if (!tube || pipe(tube) != 0)
			{
				free_commands(head);
				return (NULL);
			}
			tmp->tube = tube;
		}
		tmp = tmp->next;
	}
	return (head);
}

//takes an array of strings and parse them in an array of structures
t_command *get_commands_list(char **c, t_strlist *env)
{
	int		i;
	t_command	*head;
	t_command	*tmp;
	t_command	*current;

	i = 0;
	head = get_command(c, &i, env);
	if (!head)
		return (NULL);
	current = head;
	while (c[i] && ft_strlen(c[i]) != 0)
	{
		tmp = get_command(c, &i, env);
		if (!tmp)
			return (free_commands(head));
		tmp->prev = current;
		current->next = tmp;
		current = tmp;
	}
	head = set_command_list_tube(head);
	return (head);
}
