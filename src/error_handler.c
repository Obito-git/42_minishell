#include "minishell.h"

t_bool	find_inputfile_errors(t_command *head, char **msg, t_strlist *env)
{
	char	*tmp;

	while (head)
	{
		if (head->in_mode == IN_FILE && (!head->next
			|| access(head->next->command, R_OK) != 0))
		{
			if (!head->next)
				*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
			else
			{
				*msg = ft_str_threejoin(HEADER, head->next->command, ": ");
				tmp = *msg;
				*msg = ft_strjoin(*msg, "No such file or directory\n");
				free(tmp);
				env->ret = 1;	
			}
			return (TRUE);
		}
		head = head->next;
	}
	return (FALSE);
}

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
	if (last->prev && last->prev->pipe && !last->path_to_bin)
	{
		tmp = ft_strjoin(last->command, ": ");
		*msg = ft_str_threejoin(HEADER, tmp, "command not found\n");
		free(tmp);
		env->ret = 127;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	check_command_syntax(t_command *head, char **msg)
{
	t_command *last;

	*msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
	last = get_last_cmd(head);
	if (last->out_mode || last->in_mode)
		return (TRUE);
	else
	{
		while (head)
		{
			if (ft_strlen(head->command) == 0)
				return (TRUE);
			head = head->next;
		}
	}
	free(*msg);
	return (FALSE);
}

t_command   *find_syntax_errors(t_command *head, t_strlist *env)
{
	char		*msg;

	msg = NULL;
	env->ret = 258;
	if (check_command_syntax(head, &msg))
		;
	else if (check_pipe_syntax(head, &msg, env))
		;
	else if (check_unexpected_token(head, &msg))
		;
	else if (find_inputfile_errors(head, &msg, env))
		;
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