#include "minishell.h"

/*HANDLERS*/

static void	print_newline(int signal)
{
	(void) signal;
	write(1, "\n", 1);
}

void	interactive_sigint_handler(int signal)
{
	(void) signal;

	write(1, "\n", 1); // Move to a new line
    rl_on_new_line(); // Regenerate the prompt on a newline
    rl_replace_line("", 0); // Clear the previous text
    rl_redisplay();
}

/*SETTERS*/

void	set_interactive_sigint_handling(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &interactive_sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	set_noninteractive_signal_handling(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &print_newline;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*IGNORE*/

void	ignore_sigint(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

void	ignore_siquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*RESET*/

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

