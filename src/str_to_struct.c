#include "minishell.h"

//returns args (array of strings) deleting multiple spaces and external quotes
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
}

//return parsed struct
t_command *get_command(char *c, t_strlist *env)
{
	int			y;
	t_command	*res;

	y = 0;
	res = command_init(c, 0, 0, 0);
	if (!res)
		return (NULL);
	while (res->command[y] && res->command[y] != ' '
			&& !is_pipe_redir(res->command[y]))
		y++;
	res->command[y] = '\0';
	res->path_to_bin = find_command(env->envp, res);
	set_command_args(res, c, y);
	if (!res->args)
	{
		free_commands(res);
		return (NULL);
	}
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
	head = get_command(c[i++], env);
	if (!head)
		return (NULL);
	current = head;
	while (c[i] && ft_strlen(c[i]) != 0)
	{
		tmp = get_command(c[i], env);
		if (!tmp)
			return (free_commands(head));
		tmp->prev = current;
		current->next = tmp;
		current = tmp;
		i++;
	}
	head = set_command_list_tube(head);
	return (head);
}
