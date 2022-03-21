#include "minishell.h"

int	xit(void *args, t_strlist *env)
{
	t_command	*head;

	head = (t_command *) args;
	printf("exit\n");
	free_commands(head);
	free_strlist(env);
	exit(0);
}
