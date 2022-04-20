/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:07:33 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 15:07:33 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pathname_access(t_command *c)
{
	char	*msg;
	int		ret;

	ret = 0;
	msg = ft_strjoin(HEADER, c->command);
	if (!c->path_to_bin && (!ft_strncmp("./", c->command, 2)
			|| ft_strchr(c->command, '/')))
	{
		if ((access(c->command, X_OK) == -1 || access(c->command, F_OK) == -1)
			&& !is_directory(c->command))
			perror(msg);
		else if (is_directory(c->command) || contains_only(c->command, '/'))
			ft_dprintf_str(2, "%s%s: is a directory\n", HEADER, c->command);
		if ((access(c->command, F_OK) == 0 && access(c->command, X_OK) == -1)
			|| is_directory(c->command) || contains_only(c->command, '/'))
			ret = 126;
		else if (access(c->command, F_OK) == -1)
			ret = 127;
		else
			c->path_to_bin = ft_strdup(c->command);
	}
	free(msg);
	return (ret);
}

bool	find_elementary_errors(char **s, t_strlist *env)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (!s)
		return (true);
	while (s[i])
	{
		y = 0;
		while (s[i][y] && is_pipe_redir_char(s[i][y]))
			y++;
		if (ft_strlen(s[i]) > 0 && !s[i][y] && !is_pipe_redir(s[i]))
		{
			ft_dprintf_str(2, "%s%s\"%s\"\n", HEADER, ERROR_SYNTAX, s[i]);
			env->ret = 2;
			return (true);
		}
		i++;
	}
	return (false);
}

t_command	*parse(char *user_input, t_strlist *env)
{
	t_command	*head;
	t_strlist	*list;

	head = NULL;
	list = expand_pipeline(user_input, env);
	if (!list)
		return (NULL);
	if (!list->head)
	{
		free(list);
		return (NULL);
	}
	update_strlist_strarr_value(list);
	if (find_elementary_errors(list->strarr_value, env))
	{
		free_strlist(list);
		return (head);
	}
	head = get_commands_list(list->strarr_value, env);
	free_strlist(list);
	return (head);
}
