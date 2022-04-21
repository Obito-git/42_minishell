/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:02:13 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:02:13 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	check_unexpected_token(t_command *head)
{
	while (head)
	{
		if (!head->command && !head->infile && !head->outfile)
		{
			ft_dprintf_str(2, "%s%s", HEADER, ERROR_SYNTAX);
			if (head->pipe)
				ft_dprintf_str(2, "\'|\'\n");
			else if (head->infile || head->outfile)
			{
				if (head->infile)
					ft_dprintf_str(2, "\'<\'\n");
				else
					ft_dprintf_str(2, "\'>\'\n");
			}
			return (true);
		}
		if ((head->infile && !head->infile->filename)
			|| (head->outfile && !head->outfile->filename))
		{
			ft_dprintf_str(2, "%s%s\'newline\'\n", HEADER, ERROR_SYNTAX);
			return (true);
		}
		head = head->next;
	}
	return (false);
}

void	refresh_heredoc_fd(t_redir **red, t_command *head,
		t_command *c, bool iterate)
{
	if ((*red)->mode == IN_HEREDOC)
	{
		if ((*red)->heredoc_fd != -1)
			close((*red)->heredoc_fd);
		(*red)->heredoc_fd = get_heredoc_fd((*red)->filename, head, c, *red);
	}
	if (iterate)
		*red = (*red)->next;
}

char	*check_access(t_command *c, t_command *head)
{
	t_redir	*tmp;
	t_redir	*iter;

	tmp = c->infile;
	while (tmp)
	{
		if (tmp->mode == IN_FILE && access(tmp->filename, R_OK) == -1)
		{
			iter = tmp;
			while (iter)
				refresh_heredoc_fd(&iter, head, c, true);
			return (tmp->filename);
		}
		refresh_heredoc_fd(&tmp, head, c, false);
		tmp = tmp->next;
	}
	tmp = c->outfile;
	return (NULL);
}

bool	check_filenames(t_command *head, t_strlist *env)
{
	char		*err;
	t_command	*tmp;

	tmp = head;
	while (tmp)
	{
		err = check_access(tmp, head);
		if (err)
		{
			access(err, R_OK);
			ft_dprintf_str(2, "%s", HEADER);
			perror(err);
			env->ret = 1;
			tmp->to_execute = false;
		}
		tmp = tmp->next;
	}
	return (env->ret == 1);
}

t_command	*find_syntax_errors(t_command *head, t_strlist *env)
{
	if (!head)
		return (NULL);
	if (head->command && !ft_strlen(head->command))
		return (free_commands(head));
	env->ret = 2;
	if (check_unexpected_token(head) || check_filenames(head, env))
		;
	else
	{
		env->ret = 0;
		return (head);
	}
	if (env->ret == 1)
		return (head);
	free_commands(head);
	return (NULL);
}
