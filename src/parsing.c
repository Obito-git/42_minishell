#include "../minishell.h"


t_command	*parse(char *com)
{
	t_command	*res;
//	int			i;

//	i = 0;
	/*
	while (com[i])
	{

		if (com[i] == '|' || com[i] == '>' || com[i] == '<')
		{
			//do smthing
		}

		i++;
	}
	*/
	res = command_init(com, 0, 0, 0);
	return (res);
}
