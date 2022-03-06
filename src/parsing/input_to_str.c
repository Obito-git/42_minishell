#include "../../minishell.h"

//returns malloced substring with command, args and pipe/redirection
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
	res = (char **) malloc(sizeof(char *) * (ft_strlen(s) + 1)); //malloc prot
	com_count = 0;
    while(res && s && s[*i])
	{
		set_quotes(s[*i], &inside_quotes, &inside_double_quotes);
		if (is_pipe_redir(s[*i])
			&& (!inside_quotes && !inside_double_quotes))
			res[com_count++] = cut_command(s, &start, i);
		*i += 1;
	}
	if (res)
	{
		res[com_count++] = cut_command(s, &start, i);
		res[com_count] = NULL;
	}
	return (res);
}

//returns args deleting multiple spaces and external quotes
char	**parse_command_args(char *command)
{
	int		i;
	char	**res;

	i = 0;
	while (command[i] && command[i] != '\'' && command[i] != '\"')
		i++;
	if (!command[i])
		return (ft_split(command, ' '));
	if (command[i] == '\'')
		res = ft_split(command, '\'');
	else
		res = ft_split(command, '\"');
	res = ft_strtrim_array(res, " ");
	return (res);
}
