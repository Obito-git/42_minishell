#include "minishell.h"

//closes all the tubes of the array list except current.
//used to close the tubes inside the child's process
void	close_extra_tubes(t_command *head, t_command *current)
{
	while (head)
	{
		if (head != current && head->pipe)
		{
			close(head->tube[0]);
			close(head->tube[1]);
		}
		head = head->next;
	}
}

int	try_to_execute(t_command *c, t_strlist *env)
{
	reset_sigquit(); //is it good place for this function?
	if (!c->path_to_bin)
	{
		ft_dprintf_str(STDERR_FILENO, "%s", HEADER);
		ft_dprintf_str(STDERR_FILENO, "%s: command not found\n", c->command);
	}
	else
		return (execve(c->path_to_bin, c->args, env->envp));
	return (EXIT_UNK_CMD);
}

//Tries to execute built-in if possible, if not tries to execute a binary file;
// calls all input/output files and pipe functions
void	exec_com(t_command *head, t_command *c, t_strlist *env)
{
	int		(*built_in)(t_command*, t_strlist*);
	t_inout_fd	*inout;
	int 	ret;

	ret = 0;
	inout = set_redirections(c, head, env);
	set_tubes_path(head, c);
	built_in = get_built_in(c);
	if (inout && built_in)
		ret = built_in(c, env);
	else if (inout)
		ret = try_to_execute(c, env);
	if (!inout)
		ret = EXIT_FAILURE;
	close_fds(inout);
	free_commands(head);
	free_strlist(env);
	exit(ret);
}

//childs runner
void	run_childs(t_command *head, t_strlist *env)
{
	t_command	*tmp;
	int			pid;

	tmp = head;
	pid = -1;
	while (pid != 0 && tmp)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork: ");
		else if (pid == 0)
			exec_com(head, tmp, env);
		tmp = tmp->next;
		while (tmp && (tmp->prev && (tmp->prev->in_mode || tmp->prev->out_mode)))
			tmp = tmp->next;
	}
}

/* Creates child processes, calls execution of commands and waits for their execution.
* The main function of the executor
*/
int	execute_pipeline(t_command *head, t_strlist *env)
{
	int			wstatus;
	int			(*built_in)(t_command*, t_strlist*);

	built_in = NULL;
	if (head->next == NULL)
		built_in = get_built_in(head);
	if (built_in)
		return (built_in(head, env));
	run_childs(head, env);
	close_extra_tubes(head, NULL);
	while (waitpid(-1, &wstatus, 0) != -1 || errno != ECHILD)
		;
	return (WEXITSTATUS(wstatus));
}
