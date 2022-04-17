#include "minishell.h"

bool	check_unexpected_token(t_command *head, char **msg)
{
	while (head)
	{
		if (head->pipe && head->prev && !ft_strlen(head->command))
		{
			if (head->prev->out_mode)
				*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
			else
				*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'|\'\n");
			return (true);
		}
		head = head->next;
	}
	return (false);
}

bool	check_pipe_syntax(t_command *head, char **msg, t_strlist *env)
{
	t_command	*last;
	char		*tmp;

	if (ft_strlen(head->command) == 0 && head->pipe)
	{
		*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'|\'\n");
		return (true);
	}
	last = get_last_cmd(head);
	if (last->prev && last->prev->pipe
		&& (!last->path_to_bin && (ft_strlen(last->command)
				&& ft_strncmp("./", last->command, 2)
				&& !ft_strchr(head->command, '/'))))
	{
		tmp = ft_strjoin(last->command, ": ");
		*msg = ft_str_threejoin(HEADER, tmp, "command not found\n");
		free(tmp);
		env->ret = 127;
		return (true);
	}
	return (false);
}

bool	check_command_syntax(t_command *head, char **msg, t_strlist *env)
{
	*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
	while (head)
	{
		if (ft_strlen(head->command) && head->in_mode && !head->path_to_bin
			&& !ft_strchr(head->command, '/'))
		{
			free(*msg);
			*msg = ft_str_threejoin(head->command, ": ", "command not found\n");
			env->ret = 127;
			return (true);
		}
		if (ft_strlen(head->command) == 0 && !head->pipe
			&& !head->in_mode && !head->out_mode)
			return (true);
		head = head->next;
	}
	free(*msg);
	return (false);
}

bool	check_pipes_redir(t_command *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (is_pipe_redir_char(head->command[i]))
			i++;
		if (!head->command[i])
		{
			ft_dprintf_str(2, "%ssyntax error near unexpected token \n", HEADER);
			return (true);
		}
		head = head->next;
	}
	return (false);
}

t_command	*find_syntax_errors(t_command *head, t_strlist *env)
{
	char		*msg;

	if (!head)
		return (NULL);
	if (ft_strlen(head->command) == 0 && !head->in_mode && !head->out_mode
		&& !head->pipe)
		return (free_commands(head));
	msg = NULL;
	env->ret = 2;
	if (check_pipes_redir(head)
		|| check_command_syntax(head, &msg, env)
		|| check_pipe_syntax(head, &msg, env)
		|| check_unexpected_token(head, &msg))
		;
	else if (get_last_cmd(head)->out_mode || get_last_cmd(head)->in_mode)
		msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
	else
	{
		env->ret = 0;
		return (head);
	}
	ft_putstr_fd(msg, 2);
	free_commands(head);
	free(msg);
	return (NULL);
}
