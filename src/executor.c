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

//Tries to find the command
char	*find_command(char **envp, t_command *c)
{
	char	**splited;
	int		i;
	char	*test_path;

	i = 0;
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	splited = ft_split(*envp, ':');
	while (splited && splited[i++])
	{
		test_path = ft_str_threejoin(splited[i], "/", c->command);
		if (!test_path || access(test_path, X_OK) == 0)
			break ;
		free(test_path);
		test_path = NULL;
	}
	i = 0;
	while (splited && splited[i])
		free(splited[i++]);
	free(splited);
	return (test_path);
}

//Tries to execute_pipeline the command
void	exec_com(t_command *head, t_command *c, t_strlist *env)
{
	char	*path;
	int		out_fd;
	int		in_fd;
	int		(*built_in)(t_command*, t_strlist*);
	int 	ret;

	path = NULL;
	ret = 0;
	out_fd = set_out_path(c);
	in_fd = set_in_path(head, c);
	if (in_fd != -1 && out_fd == -1 && c->next)
		out_fd = set_out_path(c->next);
	set_tubes_path(head, c);
	built_in = get_built_in(c);
	if (built_in)
		ret = built_in(c, env);
	else
	{
		path = find_command(env->envp, c);
		if (!path && (!c->prev || (!c->prev->out_mode && !c->prev->in_mode)))
		{
			printf("Unknown command %s\n", c->command); //Should go to stderr
			exit(EXIT_FAILURE);
		}
		else if (path && (!c->prev || (!c->prev->out_mode && !c->prev->in_mode)))
			ret = execve(path, c->args, env->envp);
	}
	close(out_fd);
	close(in_fd);
	free(path);
	free_commands(head);
	exit(ret);
}

/* Creates child processes, calls execution of commands and waits for their execution.
* The main function of the executor
*/
int	execute_pipeline(t_command *head, t_strlist *env)
{
	t_command	*tmp;
	int			pid;
	int			wstatus;
	int			(*built_in)(t_command*, t_strlist*);


	built_in = NULL;
	if (head->next == NULL)
		built_in = get_built_in(head);
	if (built_in)
		return (built_in(head, env));
	pid = -1;
	tmp = head;
	while (pid != 0 && tmp)
	{
		pid = fork();
		if (pid == -1)
			perror("Fork");
		else if (pid == 0)
			exec_com(head, tmp, env);
		tmp = tmp->next;
	}
	close_extra_tubes(head, NULL);
	while (waitpid(-1, &wstatus, 0) != -1 || errno != ECHILD)
		;
	return (WEXITSTATUS(wstatus));
}