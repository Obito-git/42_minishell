#include "minishell.h"

void command_print(t_command **c)
{
	int y = 0;
	if (!c)
		printf("Command is null\n");
	else
	{
		while (c && c[y])
		{
			int i = 0;
			printf("Command: %s\n", c[y]->command);
			printf("Args: ");
			if (!c[y]->args)
				printf("Args null");
			if (!c[y]->args[i])
				printf("No args");
			while (c[y]->args && c[y]->args[i])
			{
				printf(" [%s] ", c[y]->args[i]);
				i++;
			}
			printf("\nPipe: %s", c[y]->pipe ? "YES\n" : "NO\n");
			if (c[y]->out_mode)
				printf("OUT: %s", c[y]->out_mode == 1 ? "REWRITE\n" : "APPEND\n");
			if (c[y]->in_mode)
				printf("IN: %s", c[y]->in_mode == 1 ? "SOLO\n" : "MULTU\n");
			printf("------------------\n");
			y++;
		}
	}
}

int main(int ac, char **av)
{
	char        *user_input;
	t_command	**com;

	if (ac != 1)
	{
		printf("You can't have args\n");
		(void) av;
		return (1);
	}
	while (1)
	{
		user_input = readline("minishell$ ");
		if (!user_input)
		{
			printf("exit\n");
			break;
		}
		if (ft_strlen(user_input))
		{
			add_history(user_input);
			com = parse(user_input);
		}
		free(user_input);
		command_print(com);
	}
	return (0);
}
