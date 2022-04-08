#include "minishell.h"

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
		com->pipe = true;
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
	}
}

//return parsed struct
t_command	*get_command(char **c, int *pos, t_strlist *env)
{
	t_command	*res;

	res = command_init();
	if (!res)
		return (NULL);
	if (!ft_strcmp(c[*pos], "<") || !ft_strcmp(c[*pos], "<<"))
		res->command = ft_strdup("");
	else
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
t_command	*get_commands_list(char **c, t_strlist *env)
{
	int			i;
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
