#include "../../minishell.h"

//returns args deleting multiple spaces and external quotes
char	**parse_command_args(char *command)
{
	int		i;
	char	**res;

	i = 0;
	if (!command)
		return (NULL);
	if (!command[0])
	{
		res = (char **) malloc(sizeof(char *));
		if (!res)
			return (NULL);
		res[0] = NULL;
		return (res);
	}
	while (command[i] && command[i] != '\'' && command[i] != '\"')
		i++;
	if (!command[i])
		return (ft_split(command, ' '));
	if (command[i] == '\'')
		res = ft_split(command, '\'');
	else
		res = ft_split(command, '\"');
	res = ft_strtrim_array(res, " ");
	return (res);
}

t_bool	set_command_args(t_command *c, char *s, int i, int y)
{
	t_bool	inside_quotes;
	t_bool	inside_double_quotes;
	char	*tmp;

	inside_quotes = FALSE;
	inside_double_quotes = FALSE;
	if (!c || !s)
		return (FALSE);
	while(s[y])
	{
		set_quotes(s[y], &inside_quotes, &inside_double_quotes);
		if (!inside_quotes && !inside_double_quotes && is_pipe_redir(s[y]))
			break ;
		y++;
	}
	set_command_redir(c, &s[y]);
	tmp = ft_strtrim(&s[i], " ");
	if (!tmp)
		return (FALSE);
	c->args = parse_command_args(tmp);
	free(tmp);
	return (TRUE);
}

//return parsed struct
t_command *get_command(char *c)
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
	res->command[y] = 0;
	if (!set_command_args(res, c, y, y) || !res->args)
	{
		return (NULL); //free all and return null
	}
	return (res);
}

//takes an array of strings and parse them in an array of structures
t_command *get_commands_list(char **c)
{
	int		i;
	t_command	*head;
	t_command	*tmp;
	t_command	*current;

	i = 0;
	head = get_command(c[i++]);
	if (!head)
		return (NULL);
	current = head;
	while (c[i])
	{
		tmp = get_command(c[i]);
		if (!tmp)
		{
			return (NULL); //free all
		}
		current->next = tmp;
		current = tmp;
		i++;
	}
	return (head);
}
