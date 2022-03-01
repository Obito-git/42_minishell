#include "../minishell.h"
void	set_quotes(char c, t_bool *q, t_bool *dq)
{
	if (c == '\'' && !*q)
	{
		*q = TRUE;
		//printf("Inside \'\n");
	}
	else if (c == '\'' && *q)
	{
		*q = FALSE;
		//printf("Outside \'\n");
	}
	if (c == '\"' && !*dq)
	{
		*dq = TRUE;
		//printf("Inside \"\n");
	}
	else if (c == '\"' && *dq)
	{
		*dq = FALSE;
		//printf("Outside \"\n");
	}
}

char	*cut_command(char *s, int *start, int *end)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *) ft_calloc(ft_strlen(s), sizeof(char));
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

//delete command from user_int pointer and returns it
char	**get_all_commands(char *s, int *i)
{
	t_bool inside_quotes;
	t_bool inside_double_quotes;
	char	**res;
	int		start;
	int		com_count;

	inside_quotes = FALSE;
	inside_double_quotes = FALSE;
	start = 0;
	while (s[start++])
		if (s[start] == '|' || s[start] == '<' || s[start] == '>')
			com_count++;
	start = 0;
	res = (char **) malloc(sizeof(char *) * (com_count + 2));
	com_count = 0;
	while(res && s && s[*i])
	{
		set_quotes(s[*i], &inside_quotes, &inside_double_quotes);
		if (((s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
			&& (!inside_quotes && !inside_double_quotes)))
				res[com_count++] = cut_command(s, &start, i);
		*i += 1;
	}
	res[com_count++] = cut_command(s, &start, i);
	res[com_count] = NULL;
	return (res);
}

t_command	*parse(char *com)
{
	char **commands;
	int i = 0;

	commands = get_all_commands(com, &i);
	i = 0;
	if (!commands)
		printf("Commands == NULL\n");
	while (commands && commands[i])
	{
		printf("res[%s]\n", commands[i]);
		i++;
	}
	return (NULL);
}
