#include "minishell.h"

void command_print(t_command *c)
{
    if (!c)
        printf("Command is null\n");
    else
    {
		while (c)
		{
 	       printf("Command: %s\n", c->command);
 	       printf("Pipe: %s", c->pipe ? "YES\n" : "NO\n");
 	       if (c->out_mode)
 	           printf("OUT: %s", c->out_mode == 1 ? "REWRITE\n" : "APPEND\n");
 	       if (c->in_mode)
 	           printf("IN: %s", c->out_mode == 1 ? "SOLO\n" : "MULTU\n");
			printf("------------------\n");
			c = c->next;
		}
    }
}

int main(void)
{
	char        *user_input;
	//t_command	*com;

	while (1)
	{
		user_input = readline("minishell$ ");
		if (!user_input)
		{
			printf("exit\n");
			break;
		}
		parse(user_input);
	//	command_print(com);
	}
	return (0);
}
