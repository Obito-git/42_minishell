#include "../minishell.h"
t_command	*set_command_vars(char *s, int from, int to)
{
	t_command	*res;

	res = command_init();
	if (!res)
		return (NULL);
	if (s[from] == '<')

}

t_command	*parse(char *com)
{
	t_command	*head;
	t_command	*res;
	int			i;
	int			y;
	char		**s;

	i = 0;
	y = 0;
	while (s[i])
	{
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			y = i;
		}
		i++;
	}
	return (res);
}
