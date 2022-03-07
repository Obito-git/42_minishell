#include "../../minishell.h"

//working like split but not touching the content inside quotes;
//need delete 2 lines for norminette, args z and i used also for the economize lines
char	**ft_minishell_split(char **res, char *s, int z, int i)
{
	int		y;
	t_bool	q;
	t_bool	dq;

	res = (char **) malloc(sizeof(char *) * (z + 1));
	q = FALSE;
	dq= FALSE;
	z = 0;
	i = 0;
	y = 0;
	while (res && s[i])
	{
		set_quotes(s[i], &q, &dq);
		if ((s[i] == ' ' && !q && !dq) || !s[i + 1])
		{
			res[y++] = ft_substr(s, z, i - z + 1);
			if (!res[y - 1])
				return (free_strarray(res));
			while (s[i] && s[i + 1] && s[i + 1] == ' ')
				i++;
			z = i;
		}
		res[y] = NULL;
		i++;
	}
	res = ft_strtrim_array(res, " \"\'");
	return (res);
}

//returns args deleting multiple spaces and external quotes
char	**parse_command_args(char *command)
{
	char	**res;
	int		i;
	int		size;

	i = 0;
	size = 1;
	res = NULL;
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
	while (command[i]) // try to put iteration of i inside if condition
	{
		if (i > 0 && command[i] == ' ' && command[i - 1] != ' ')
			size++;
		i++;
	}
	res = ft_minishell_split(res, command, size, i);
	return (res);
}

//set redir/pipe value inside struct and delete it with main command to prepare "clear" args to send
//it in char	**parse_command_args(char *command);
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
