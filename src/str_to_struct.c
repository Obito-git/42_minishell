/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:05:59 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:05:59 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redirections(t_command *com, char **s, int *pos)
{
	char	*mode;
	char	*name;

	mode = s[*pos];
	name = s[*pos + 1];
	if (!ft_strcmp(name, "|"))
		name = NULL;
	if (!ft_strcmp(mode, ">>") || !ft_strcmp(mode, ">"))
		com->outfile = append_redir(com->outfile, mode, name);
	else
		com->infile = append_redir(com->infile, mode, name);
	*pos += 1;
	if (s[*pos] && ft_strcmp(s[*pos], "|"))
		*pos += 1;
}

void	set_pipe_and_redir(t_command *com, int *pos)
{
	com->pipe = true;
	*pos += 1;
}

//return parsed struct
t_command	*get_command(char **c, int *pos, t_strlist *env)
{
	t_command	*res;

	res = command_init();
	if (!res)
		return (NULL);
	while (c[*pos] && ft_strcmp(c[*pos], "|"))
	{
		while (is_pipe_redir(c[*pos]) && ft_strcmp(c[*pos], "|"))
			parse_redirections(res, c, pos);
		if (!res->command && !is_pipe_redir(c[*pos]) && c[*pos])
		{
			res->command = ft_strdup(c[*pos]);
			res->args = ft_append_strarray(NULL, res->command);
		}
		else if (!is_pipe_redir(c[*pos]) && c[*pos])
			res->args = ft_append_strarray(res->args, c[*pos]);
		/*
		if ((!res->args || !res->command) && c[*pos])
			return (free_commands(res));
		*/
		if (!is_pipe_redir(c[*pos]) && c[*pos])
			*pos += 1;
	}
	if (c[*pos] && !ft_strcmp(c[*pos], "|"))
		set_pipe_and_redir(res, pos);
	res->path_to_bin = find_command(env->strarr_value, res);
	return (res);
}

t_command	*set_command_list_tube(t_command *head)
{
	int			*tube;
	t_command	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->pipe)
		{
			tube = (int *) malloc(sizeof(int) * 2);
			if (!tube || pipe(tube) != 0)
			{
				free_commands(head);
				return (NULL);
			}
			tmp->tube = tube;
		}
		tmp = tmp->next;
	}
	return (head);
}

//takes an array of strings and parse them in an array of structures
t_command	*get_commands_list(char **c, t_strlist *env)
{
	int			i;
	t_command	*head;
	t_command	*tmp;
	t_command	*current;

	i = 0;
	head = get_command(c, &i, env);
	if (!head)
		return (NULL);
	current = head;
	while (c[i] && ft_strlen(c[i]) != 0)
	{
		tmp = get_command(c, &i, env);
		if (!tmp)
			return (free_commands(head));
		tmp->prev = current;
		current->next = tmp;
		current = tmp;
	}
	head = set_command_list_tube(head);
	return (head);
}
