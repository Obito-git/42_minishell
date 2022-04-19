/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:59:22 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:59:22 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	used for the initialision of t_command structure with default values
*/
t_command	*command_init(void)
{
	t_command	*res;

	res = (t_command *) malloc(sizeof(t_command));
	if (!res)
		return (NULL);
	res->command = NULL;
	res->path_to_bin = NULL;
	res->tube = NULL;
	res->args = NULL;
	res->pipe = false;
	res->infile = NULL;
	res->outfile = NULL;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

//tries to delete heredoc tmpfile
void	delete_tmpfiles(t_command *head)
{
	char		*filename;
	t_command	*tmp_cmd;
	t_redir		*tmp_red;

	if (head)
	{
		tmp_cmd = head;
		while (tmp_cmd)
		{
			tmp_red = tmp_cmd->infile;
			while (tmp_red)
			{
				if (tmp_red->mode == IN_HEREDOC)
				{
					filename = get_heredoc_tmpname(head, tmp_cmd, tmp_red);
					if (filename)
						unlink(filename);
					free(filename);
				}
				tmp_red = tmp_red->next;
			}
			tmp_cmd = tmp_cmd->next;
		}
	}
}

//applies free on each element of an array list
t_command	*free_commands(t_command *c)
{
	t_command	*tmp;
	int			i;

	delete_tmpfiles(c);
	if (c)
	{
		while (c)
		{
			free(c->command);
			free(c->path_to_bin);
			free(c->tube);
			free_redir(c->infile);
			free_redir(c->outfile);
			i = 0;
			while (c->args && c->args[i])
			{
				free(c->args[i]);
				i++;
			}
			free(c->args);
			tmp = c->next;
			free(c);
			c = tmp;
		}
	}
	return (NULL);
}

t_command	*get_last_cmd(t_command *head)
{
	t_command	*tmp;

	tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_command	*free_commands_strlist(t_command *c, t_strlist *l)
{
	free_strlist(l);
	free_commands(c);
	return (NULL);
}
