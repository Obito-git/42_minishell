#include "minishell.h"

t_bool	find_inputfile_errors(t_command *head, char **msg, char *header)
{
	char	*tmp;

	while (head)
	{
		if (head->in_mode == IN_FILE && (!head->next
			|| access(head->next->command, R_OK) != 0))
		{
			if (!head->next)
				*msg = ft_strjoin(header, "syntax error near unexpected token `newline'\n");
			else
			{
				*msg = ft_str_threejoin(header, head->next->command, ": ");
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

t_command   *find_syntax_errors(t_command *head)
{
	char		*msg;
	char		*header;
	t_command	*last;

	header = ft_strdup("minishell: ");
	last = head;
	msg = NULL;
	while (last->next)
		last = last->next;
	if (ft_strlen(head->command) == 0 && head->pipe)
		msg = ft_strjoin(header, "syntax error near unexpected token `|'\n");
	else if (last->out_mode)
		msg = ft_strjoin(header, "syntax error near unexpected token `newline'\n");
	else if (find_inputfile_errors(head, &msg, header))
		;
	else
	{
		free(header);
		return (head);
	}
	ft_putstr_fd(msg, 2);
	free_commands(head);
	free(header);
	free(msg);
	return (NULL);
}