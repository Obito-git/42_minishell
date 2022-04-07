/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:28:19 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/06 16:28:19 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	cd_errors (char *path)
{
	int		ret;
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd: error retrieving current directory: getcwd: cannot access parent directories");
		return (0);
	}
	ret = chdir(path);
	if (ret)
	{
		ft_dprintf_str(2,
			"minishell: cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (ret);
}

int	cd(t_command *cmd, t_strlist *env)
{
	char	**paths;

	(void) env;
	paths = cmd->args;
	paths++;
	if (!paths[0])
	{
		ft_dprintf_str(2, "minishell: cd: you must provide a path\n");
		return (1);
	}
	if (paths[0] && paths[1])
	{
		ft_dprintf_str(2, "minishell: cd: too many arguments\n");
		return (1);
	}
	return (cd_errors(paths[0]));
}
