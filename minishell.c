#include "minishell.h"

void command_print(t_command *c)
{
	if (!c)
		printf("Command is null\n");
	else
	{
		while (c)
		{
			int i = 0;
			printf("Command: %s\n", c->command);
			printf("Args: ");
			if (!c->args)
				printf("Args null");
			if (!c->args[i])
				printf("No args");
			while (c->args && c->args[i])
			{
				printf(" [%s] ", c->args[i]);
				i++;
			}
			printf("\nPipe: %s", c->pipe ? "YES\n" : "NO\n");
			if (c->out_mode)
				printf("OUT: %s", c->out_mode == 1 ? "REWRITE\n" : "APPEND\n");
			if (c->in_mode)
				printf("IN: %s", c->in_mode == 1 ? "SOLO\n" : "MULTU\n");
			printf("------------------\n");
			c = c->next;
		}
	}
}

int main(int ac, char **av)
{
	char        *user_input;
	t_command	*head;

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
			head = parse(user_input);
		}
		free(user_input);
		command_print(head);
	}
	return (0);
}
