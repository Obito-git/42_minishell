#include "minishell.h"

void set_signal_handling()
{
	struct sigaction sa;

	sa.sa_handler = &sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	sigint_handler(int signal)
{
	(void) signal;
	write(1, REPROMPT, sizeof(REPROMPT) - 1);
}
