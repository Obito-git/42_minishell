/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:57:34 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 14:57:34 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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

void	ignore_siquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
