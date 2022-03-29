#include "minishell.h"

void command_print(t_command *c)
{
	if (!c)
		printf("Command is null\n");
	else
	{
		while (c)
		{
			int i = 0;
			printf("Command: %s\n", c->command);
			printf("Args: ");
			if (!c->args)
				printf("Args null");
			if (!c->args[i])
				printf("No args");
			while (c->args && c->args[i])
			{
				printf(" [%s] ", c->args[i]);
				i++;
			}
			printf("\nPipe: %s", c->pipe ? "YES\n" : "NO\n");
			if (c->out_mode)
				printf("OUT: %s", c->out_mode == 1 ? "REWRITE\n" : "APPEND\n");
			if (c->in_mode)
				printf("IN: %s", c->in_mode == 1 ? "SOLO\n" : "MULTU\n");
			printf("PATH: %s\n", c->path_to_bin);
			printf("------------------\n");
			c = c->next;
		}
	}
}

/*	parse user input into an array list. save result in head variable
*	call the readline if there is no command after the pipe and
*	correctly displays the history in this case
*/
void	prepare_commands(char *in, t_command **head, t_strlist *env, char **h)
{
	t_command	*last;
	char		*tmp;

	*h = ft_strdup(in);
	*head = parse(in, env);
	last = get_last_cmd(*head);
	while (last && last->pipe && ft_strlen(last->command))
	{
		in = readline("> ");
		while (ft_strlen(in) == 0)
		{
			free(in);
			in = readline("> ");
		}
		last->next = parse(in, env);
		tmp = ft_str_threejoin(*h, " ", in);
		free(*h);
		free(in);
		*h = tmp;
		if (last->next)
			last->next->prev = last;
		last = get_last_cmd(*head);
	}
}

//checks main arguments
t_bool	check_main_args(int ac, char **av, char **envp, t_strlist **env)
{
	if (ac != 1 || !av)
	{
		printf("You can't have args\n");
		return (FALSE);
	}
	*env = make_strlist_from_null_terminated_str_array(envp);
	if (env == NULL)
	{
		perror("Unable to allocate for list of variables");
		return (FALSE);
	}
	printf("\e[1A");
	return (TRUE);
}

//calls all parsing functions and tries to execute user input
void	execute_userinput(t_strlist *env, char *user_input)
{
	t_command	*head;
	char		*history;

	history = NULL;
	head = NULL;
	prepare_commands(user_input, &head, env, &history);
	head = find_syntax_errors(head, env);
	command_print(head);
	/*head = NULL;*/
	if (history)
		add_history(history);
	free(history);
	if (head)
		env->ret = execute_pipeline(head, env);
	free_commands(head);
}

int main(int ac, char **av, char **envp)
{
	char        *user_input;
	t_strlist	*env;

	env = NULL;
	if (!check_main_args(ac, av, envp, &env))
		return (1);
	printf("\n");
	while (TRUE)
	{
		set_signal_handling();
		user_input = readline(PROMPT);
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
