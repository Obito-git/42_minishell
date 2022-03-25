#include "minishell.h"

t_bool	find_inputfile_errors(t_command *head, char **msg)
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

t_command   *find_syntax_errors(t_command *head, t_strlist *env)
{
	char		*msg;
	t_command	*last;

	last = head;
	msg = NULL;
	while (last->next)
		last = last->next;
	if (ft_strlen(head->command) == 0 && head->pipe)
		msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'|\'\n");
	else if (last->out_mode || last->in_mode)
		msg = ft_str_threejoin(HEADER, ERROR_SYNTAX, "\'newline\'\n");
	else if (check_unexpected_token(head, &msg))
		;
	else if (find_inputfile_errors(head, &msg))
		;
	else
		return (head);
	ft_putstr_fd(msg, 2);
	env->ret = 2;
	free_commands(head);
	free(msg);
	return (NULL);
}