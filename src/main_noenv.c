#include "minishell.h"

const char *prompt(int last_ret)
{
	if (last_ret == 130)
		return ("");
	else if (last_ret == 131)
		return ("\n" PROMPT);
	else
		return (PROMPT);
}

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
	printf("\n");
	while (true)
	{
		user_input = readline(prompt(env->ret));
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
