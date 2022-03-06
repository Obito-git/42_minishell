#include "../../minishell.h"

//returns malloced substring with command. (USED with cut_all_command func)
char    *cut_command(char *s, int *start, int *end)
{
        char    *res;
        int             i;

        i = 0;
        res = (char *) ft_calloc(ft_strlen(s) + 1, sizeof(char));
        if (!res)
                return (NULL);
        if ((s[*end] == '>' && s[*end + 1] == '>')
                || (s[*end] == '<' && s[*end + 1] == '<'))
                *end += 1;
        while (*start <= *end)
        {
                res[i] = s[*start];
                i++;
                *start += 1;
        }
        *start += 1;
        return (res);
}

//returns malloced array of string with commands/pipes/redirections.
//the contents of the quotes will be ignored
char    **cut_all_commands(char *s, int *i)
{
        t_bool inside_quotes;
        t_bool inside_double_quotes;
        char    **res;
        int             start;
        int             com_count;

        inside_quotes = FALSE;
        inside_double_quotes = FALSE;
        start = 0;
        res = (char **) malloc(sizeof(char *) * (ft_strlen(s) + 1));
        com_count = 0;
        while(res && s && s[*i])
        {
                set_quotes(s[*i], &inside_quotes, &inside_double_quotes);
                if (is_pipe_redir(s[*i])
                        && (!inside_quotes && !inside_double_quotes))
                                res[com_count++] = cut_command(s, &start, i);
                *i += 1;
        }
        res[com_count++] = cut_command(s, &start, i);
        res[com_count] = NULL;
        return (res);
}

char	**parse_command_args(char *command)
{
	int		i;
	char	**res;
	char	*tmp;

	i = 0;
	while (command[i] && command[i] != '\'' && command[i] != '\"')
		i++;
	if (!command[i])
		return (ft_split(command, ' '));
	if (command[i] == '\'')
		res = ft_split(command, '\'');
	else
		res = ft_split(command, '\"');
	i = 0;
	while (res && res[i])
	{
		tmp = ft_strtrim(res[i], " \"\'");
		free(res[i]);
		res[i] = tmp;
		i++;
	}
	return (res);
}

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
					res[i]->args = (char **) malloc(sizeof(char *)); //MALLOC PROT
                i++;
        }
        return (res);
}
