#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_strlist	*env;

	env = NULL;
	envp[0] = NULL;
	/*envp = NULL;*/
	if (!check_main_args(ac, av, envp, &env))
		return (1);
	set_signal_handling();
	while (true)
	{
		set_sigint_handling();
		user_input = readline(PROMPT);
		ignore_sigint();
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
