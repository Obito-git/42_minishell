#include "minishell.h"

int main(void)
{
    char    *command;

	while (1)
    {
        command = readline("minishell$ ");
        free(command);
    }
	return (0);
}
