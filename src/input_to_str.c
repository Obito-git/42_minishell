#include "minishell.h"

/*
*	Modifies [< 'input file' 'command'] to ['command' < 'input file']
*	Used to execute 2 patterns by the same executor function
*/
void	set_input_pattern(char **s)
{
	char	*tmp;
	char	*result;
	int		i;
	int		y;

	i = 0;
	if (!s || !s[0] || !s[1] || (ft_strcmp(s[0], "<")
			&& ft_strcmp(s[0], "<<")))
		return ;
	while (s[1][i] && s[1][i] != ' ' && !is_pipe_redir(s[1][i]))
		i++;
	if (ft_strlen(&s[1][i]) == 0 || is_pipe_redir(s[1][i]))
		return ;
	tmp = ft_strtrim(&s[1][i], " ><|");
	result = ft_str_threejoin(tmp, " ", s[0]);
	free(tmp);
	free(s[0]);
	s[0] = result;
	y = i;
	while(s[1][y] && !is_pipe_redir(s[1][y]))
		y++;
	ft_strcpy(&s[1][i], &s[1][y]);
}

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
//all '>' '<' '|' ">>" "<<" in quotes will be ignored
char    **cut_all_commands(char **com, char *s, int *i)
{
	bool quotes;
	bool d_quotes;
	int             start;
	int             com_count;

	quotes = false;
	d_quotes = false;
	start = 0;
	com_count = 0;
    while(s && s[*i])
	{
		set_quotes(s[*i], &quotes, &d_quotes);
		if (is_pipe_redir(s[*i]) && (!quotes && !d_quotes))
		{
			com[com_count++] = cut_command(s, &start, i);
			if (!com[com_count - 1])
				return (free_strarray(com));
		}
		*i += 1;
	}
	com[com_count++] = cut_command(s, &start, i);
	if (!com[com_count - 1])
		return (NULL);
	com[com_count] = NULL;
	return (com);
}

