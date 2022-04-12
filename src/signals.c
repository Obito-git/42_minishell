#include "minishell.h"

void	set_sigint_handling(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	set_sigquit_handling(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_handling(void)
{
	set_sigint_handling();
	/*set_sigquit_handling();*/
	ignore_siquit();
}

void	ignore_siquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	reset_sigint(void)
{
	struct sigaction	sa_sigint;

	ft_bzero(&sa_sigint, sizeof(sa_sigint));
	sa_sigint.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_sigint, NULL);
}

void	reset_sigquit()
{
	struct sigaction	sa_sigquit;

	ft_bzero(&sa_sigquit, sizeof(sa_sigquit));
	sa_sigquit.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	reset_signals(void)
{
	reset_sigint();
	reset_sigquit();
}

void	sigint_handler(int signal)
{
	(void) signal;
	write(1, "\n" PROMPT, sizeof("\n" PROMPT) - 1);
}

void	sigquit_handler(int signal)
{
	(void) signal;
	write(1, "\n", 1);
}
