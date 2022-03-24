#include "minishell.h"

//delete all quotes and single quotes from str
char	*command_delete_quotes(char *c)
{
	char	*res;
	int		i;

	i = 0;
	if (!c)
		return (NULL);
	res = ft_strtrim(c, " \'\"");
	while (res[i])
	{
		if (res[i] == '\'' || res[i] == '\"')
		{
			ft_strcpy(&res[i], &res[i + 1]);
			i--;
		}
		i++;
	}
	return (res);	
}

//replaces $VAR_NAME by variable name or "" if they are no value
char	*replace_var_value(char *arg, char *value, char *var_name, t_strlist *env)
{
	//malloc prot inside
	size_t	i;
	char	*res;
	char	*last_error_code;

	i = 0;
	last_error_code = ft_itoa(env->ret);
	while (ft_strncmp(&arg[i], var_name, ft_strlen(var_name)))
		i++;
	arg[i] = 0;
	i += ft_strlen(var_name);
	if (!value && last_error_code && !ft_strcmp(var_name, "$?"))
		res = ft_str_threejoin(arg, last_error_code, &arg[i]);
	else if (!value)
		res = ft_str_threejoin(arg, "", &arg[i]);
	else
		res = ft_str_threejoin(arg, value, &arg[i]);
	free(last_error_code);
	return (res);
}

//checks all t_command struct args and replace all $VAR_NAME by values
void	set_var_value(t_command *c, t_strlist *env)
{
	int				args_count;
	int				i;
	int				y;
	char			*res;
	char	*var_value;
	char	*tmp;

	args_count = 1;
	while (c->args[args_count])
	{
		i = 0;
		while (c->args[args_count][i])
		{
			y = 1;
			if (c->args[args_count][i] == '$')
			{
				res = ft_strdup(&c->args[args_count][i]);
				if (!res)
					continue ;
				while (res[y] && res[y] != '\"' && res[y] != '\''
						&& res[y] != ' ' && res[y] != '$' && res[y] != ':')
					y++;
				res[y] = 0;
				var_value = find_strlist_node_varvalue(env, &res[1]);
				tmp = replace_var_value(c->args[args_count], var_value, res, env);
				free(c->args[args_count]);
				free(res);
				c->args[args_count] = tmp;
			}
			i++;
		}
		args_count++;
	}
}

//i hope this function will parse all "quotes" and "vars" cases :D
t_bool	parse_quotes_vars(t_command *c, t_strlist *env)
{
	char	*tmp;

	tmp = command_delete_quotes(c->command);
	if (!tmp && c->command)
		return (FALSE);
	free(c->command);
	c->command = tmp;
	tmp = command_delete_quotes(c->args[0]);
	if (!tmp && c->args[0])
		return (FALSE);
	free(c->args[0]);
	c->args[0] = tmp;
	set_var_value(c, env);
	return (TRUE);
}