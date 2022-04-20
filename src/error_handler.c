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
		if (!head->command)
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

t_command	*find_syntax_errors(t_command *head, t_strlist *env)
{
	if (!head)
		return (NULL);
	if (head->command && !ft_strlen(head->command))
		return (free_commands(head));
	env->ret = 2;
	if (check_unexpected_token(head))
		;
	else
	{
		env->ret = 0;
		return (head);
	}
	free_commands(head);
	return (NULL);
}