/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn && tpouget <norminet@42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:06:44 by amyroshn && t     #+#    #+#             */
/*   Updated: 2022/04/19 15:06:44 by amyroshn && t    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_strlist	*env;

	env = NULL;
	if (!check_main_args(ac, av, envp, &env))
		return (1);
	printf("\n");
	while (true)
	{
		ignore_siquit();
		set_interactive_sigint_handling();
		user_input = readline(PROMPT);
		set_noninteractive_signal_handling();
		if (!user_input)
		{
			ft_dprintf_str(STDERR_FILENO, "exit\n");
			free_strlist(env);
			return (0);
		}
		if (ft_strlen(user_input) && ft_strcmp(user_input, "\n") != 0)
			execute_userinput(env, user_input);
		free(user_input);
	}
	return (0);
}
