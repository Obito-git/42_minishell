/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:03:10 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 11:03:10 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

bool	is_pipe_redir(char *s)
{
	if (!s)
		return (false);
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, "<<")
		|| !ft_strcmp(s, "|"));
}

bool	is_pipe_redir_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	contains_only(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (false);
	while (s[i])
	{
		if (s[i] != c)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

//Tries to find the command
char	*find_command(char **envp, t_command *c)
{
	char	**splited;
	int		i;
	char	*test_path;

	i = 0;
	splited = NULL;
	test_path = NULL;
	if (!ft_strncmp("./", c->command, 2) || ft_strchr(c->command, '/'))
		return (NULL);
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp && ft_strlen(c->command))
		splited = ft_split(*envp, ':');
	while (*envp && splited && splited[i++])
	{
		test_path = ft_str_threejoin(splited[i], "/", c->command);
		if (!test_path || access(test_path, X_OK) == 0)
			break ;
		free(test_path);
		test_path = NULL;
	}
	free_strarray(splited);
	if (!*envp && !is_directory(c->command) && c->command && !test_path && access(c->command, X_OK) == 0)
		return (ft_strdup(c->command));
	return (test_path);
}
