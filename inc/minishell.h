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

//	struct_utils.c
t_command	*command_init(char *c, t_bool p, char in, char out);
void		free_commands(t_command *c);
//	parsing.c
t_command	*parse(char *user_input);
void		set_quotes(char c, t_bool *q, t_bool *dq);
t_bool		is_pipe_redir(char c);
void		set_command_redir(t_command *c, char *s);
//	input_to_str.c
char		*cut_command(char *s, int *start, int *end);
char		**cut_all_commands(char **com, char *s, int *i);
//	str_to_struct.c
t_command	*get_commands_list(char **c);
//	utils.c
char		**free_strarray(char **s);
char		**ft_strtrim_array(char **s, char *set);
char		**ft_minishell_split(char **res, char *s, int z, int i);
//	executor.c
void		close_extra_tubes(t_command *head, t_command *current);
int			execute(t_command *head, char **envp);
//	pipes_redir.c
int			set_out_path(t_command *c);
void		set_tubes_path(t_command *head, t_command *c);
//	error_handler.c
t_command   *find_syntax_errors(t_command *head);
//built-ins
int	(*get_built_in(t_command *cmd))(void*);
int	echo(void *a);

#endif
