#include "../../minishell.h"

void	set_command_args(t_command *c, char *s, int i)
{
	t_bool	inside_quotes;
	t_bool	inside_double_quotes;
	int		y;
	char	*tmp;

	inside_quotes = FALSE;
	inside_double_quotes = FALSE;
	y = i;
	if (!c || !s || !s[i])
		return ;
	while(s[y])
	{
		set_quotes(s[y], &inside_quotes, &inside_double_quotes);
		if (!inside_quotes && !inside_double_quotes && is_pipe_redir(s[y]))
			break ;
		y++;
	}
	set_command_redir(c, &s[y]); //IF THEY ARE SMTHING AFTER ><| = ERROR
	tmp = ft_strtrim(&s[i], " "); // MALLOC PROT
	c->args = parse_command_args(tmp); //MALLOC PTOT

	free(tmp);
}

//takes an array of strings and parse them in an array of structures
t_command **get_commands_arr(char **c)
{
	int                     i;
	int                     y;
	t_command       **res;

	i = 0;
	while (c[i])
		i++;
	res = (t_command **) malloc(sizeof(t_command *) * (i + 1));
	i = 0;
	while (c[i])
	{
		y = 0;
		if (ft_strlen(c[i]) == 0)
			break ;
		res[i] = command_init(c[i], 0, 0, 0); //MALLOC PROTECT
		while (res[i]->command[y] && res[i]->command[y] != ' '
				&& !is_pipe_redir(res[i]->command[y]))
			y++;
		res[i]->command[y] = 0;
		set_command_args(res[i], c[i], y);
		if (!res[i]->args)
		{
			res[i]->args = (char **) malloc(sizeof(char *)); //MALLOC PROT
			res[i]->args[0] = NULL;
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
