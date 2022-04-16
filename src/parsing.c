#include "minishell.h"

/*
*	Modifies [< 'input file' 'command'] to ['command' < 'input file']
*	Used to execute 2 patterns by the same executor function
*/
void	set_input_pattern(char **s)
{
	char	*filename;
	char	*redir;
	size_t	i;

	i = 0;
	if (!s || !s[0] || !s[1] || !s[2])
		return ;
	if (!ft_strcmp(s[0], "<") || !ft_strcmp(s[0], "<<"))
	{
		redir = s[0];
		filename = s[1];
		while (s[i + 2] && (ft_strcmp(s[i + 2], "|")
				&& ft_strcmp(s[i + 2], ">") && ft_strcmp(s[i + 2], ">>")))
		{
			s[i] = s[i + 2];
			i++;
		}
		i = 0;
		while(s[i] && (ft_strcmp(s[i], "|")
				&& ft_strcmp(s[i], ">") && ft_strcmp(s[i], ">>")))
			i++;
		s[i - 2] = redir;
		s[i - 1] = filename;
	}
}

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
			&& !isDirectory(c->command))
			perror(msg);
		else if (isDirectory(c->command) || contains_only(c->command, '/'))
			ft_dprintf_str(2, "%s%s: is a directory\n", HEADER, c->command);
		if ((access(c->command, F_OK) == 0 && access(c->command, X_OK) == -1)
			|| isDirectory(c->command) || contains_only(c->command, '/'))
			ret = 126;
		else if (access(c->command, F_OK) == -1)
			ret = 127;
		else
			c->path_to_bin = ft_strdup(c->command);
	}
	free(msg);
	return (ret);
}

bool	update_args(t_strlist **arg, t_command **i, t_command **tmp)
{
	if ((*arg)->size > 0)
	{
		free_strarray((*tmp)->args);
		update_strlist_strarr_value(*arg);
		(*tmp)->args = ft_strarr_cpy((*arg)->strarr_value); 
		if (!(*tmp)->args)
			return (false);
		if (*i && (*i)->prev)
			*tmp = (*i)->prev;
		else
			*tmp = *i;
	}
	free_strlist(*arg);
	*arg = NULL;
	if (*tmp)
		*tmp = (*tmp)->next;
	return (true);
}

t_command	*check_files_args(t_command *head)
{
	t_command	*tmp;
	t_command	*i;
	t_strlist	*arg;
	int			err;

	tmp = head;
	while (tmp)
	{
		arg = new_strlist();
		if (!arg)
			return (free_commands(head));
		i = tmp;
		err = append_strarray_to_strlist(arg, i->args);
		i = i->next;
		while (err != -1 && i && i->prev
				&& (i->prev->out_mode || i->prev->in_mode))
		{
			err = append_strarray_to_strlist(arg, &i->args[1]);
			i = i->next;
		}
		if (!update_args(&arg, &i, &tmp) || err == -1)
			return (free_commands_strlist(head, arg));
	}
	return (head);
}

t_command	*parse(char *user_input, t_strlist *env)
{
	t_command	*head;
	t_strlist	*list;

	list = expand_pipeline(user_input, env);
	if (!list)
		return (NULL);
	if (!list->head)
	{
		free(list);
		return (NULL);
	}
	update_strlist_strarr_value(list);
	set_input_pattern(list->strarr_value);
	head = get_commands_list(list->strarr_value, env);
	if (head)
		head = check_files_args(head);
	free_strlist(list);
	return (head);
	//Where is user_input freed ?
}
