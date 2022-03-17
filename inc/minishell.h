#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define OUT_REWRITE 1
# define OUT_APPEND 2
# define IN_SOLO 1
# define IN_MULT 2

typedef struct s_command
{
	char	*command;
	char	**args;
	t_bool	pipe;
	char	in_mode;
	char	out_mode;
	int		*tube;
	struct s_command *next;
	struct s_command *prev;
}	t_command;

//STRUCT_UTILS
t_command	*command_init(char *c, t_bool p, char in, char out);
void	free_commands(t_command *c);

//PARSING
//	parsing.c
t_command *parse(char *user_input);
void	set_quotes(char c, t_bool *q, t_bool *dq);
t_bool is_pipe_redir(char c);
void	set_command_redir(t_command *c, char *s);
//	str_to_com.c
char    *cut_command(char *s, int *start, int *end);
char    **cut_all_commands(char **com, char *s, int *i);
t_command *get_commands_list(char **c);
char	**free_strarray(char **s);
char	**ft_strtrim_array(char **s, char *set);
char	**ft_minishell_split(char **res, char *s, int z, int i);
//end parsing

//pipex
char	*find_command(char **envp, t_command *c); //need to rename to find_path
void	execute(t_command *head, char **envp);
int		set_out_path(t_command *c);
void    set_tubes_path(t_command *head, t_command *c);
void	close_extra_tubes(t_command *head, t_command *current);
int		(*get_built_in(t_command *cmd))(void*);

//buil-ins
int	echo(void *a);

#endif
