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
	while (res && res[i])
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
	size_t	i;
	char	*res;
	char	*last_error_code;

	i = 0;
	last_error_code = ft_itoa(env->ret);
	if (!last_error_code)
		return (NULL);
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
void	replace_varname_by_values(t_command *c, t_strlist *env, char *s, int ac)
{
	int				y;
	char			*res;
	char	*var_value;
	char	*tmp;

	y = 1;
	res = ft_strdup(s);
	if (!res)
		return ;
	while (res[y] && res[y] != '\"' && res[y] != '\''
		&& res[y] != ' ' && res[y] != '$' && res[y] != ':')
		y++;
	res[y] = 0;
	var_value = find_strlist_node_varvalue(env, &res[1]);
	tmp = replace_var_value(c->args[ac], var_value, res, env);
	free(c->args[ac]);
	free(res);
	c->args[ac] = tmp;
}

//i hope this function will parse all "quotes" and "vars" cases :D
// deletes all quotes/single quotes from command and first arg
//replaces all $VAR_NAME to the varible value
t_bool	parse_quotes_vars(t_command *c, t_strlist *env)
{
	char	*tmp;
	int		ac;
	int		i;

	ac = 1;
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
	while (c->args[0] && c->args[ac])
	{
		i = 0;
		while (c->args[ac][i])
			if (c->args[ac][i++] == '$')
				replace_varname_by_values(c, env, &c->args[ac][i - 1], ac);
		ac++;
	}
	return (TRUE);
}
