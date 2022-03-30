#include "minishell.h"

t_bool	check_unexpected_token(t_command *head, char **msg)
{
	while (head)
	{
		if (head->pipe && head->prev && !ft_strlen(head->command))
		{
			if (head->prev->out_mode)
				*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
			else
				*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'|\'\n");
			return (TRUE);
		}
		head = head->next;
	}
	return (FALSE);
}

t_bool	check_pipe_syntax(t_command *head, char **msg, t_strlist *env)
{
	t_command	*last;
	char		*tmp;

	if (ft_strlen(head->command) == 0 && head->pipe)
	{
		*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'|\'\n");
		return (TRUE);
	}
	last = get_last_cmd(head);
	if (last->prev && last->prev->pipe
		&& (!last->path_to_bin && ft_strlen(last->command)))
	{
		tmp = ft_strjoin(last->command, ": ");
		*msg = ft_str_threejoin(HEADER, tmp, "command not found\n");
		free(tmp);
		env->ret = 127;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_command_syntax(t_command *head, char **msg, t_strlist *env)
{
	*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
	while (head)
	{
		if (ft_strlen(head->command) && head->in_mode && !head->path_to_bin)
		{
			free(*msg);
			*msg = ft_str_threejoin(head->command, ": ", "command not found\n");
			env->ret = 127;
			return (TRUE);
		}
		if (ft_strlen(head->command) == 0 && !head->pipe
			&& !head->in_mode && !head->out_mode)
			return (TRUE);
		head = head->next;
	}
	free(*msg);
	return (FALSE);
}

t_command   *find_syntax_errors(t_command *head, t_strlist *env)
{
	char		*msg;

	msg = NULL;
	env->ret = 2;
	if (check_command_syntax(head, &msg, env)
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