#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define TRUE 1
#define FALSE 0
#define OUT_REWRITE 1
#define OUT_APPEND 2
#define IN_SOLO 1
#define IN_MULT 2

typedef struct s_command
{
	char	*command;
	char	**args;
	t_bool	pipe;
	char	in_mode;
	char	out_mode;
	struct s_command *next;
}	t_command;

//STRUCT_UTILS
t_command	*command_init(char *c, t_bool p, char in, char out);
void	free_commands(t_command *c);

//PARSING
//	parsing.c
t_command *parse(char *com);
void	set_quotes(char c, t_bool *q, t_bool *dq);
t_bool is_pipe_redir(char c);
void	set_command_redir(t_command *c, char *s);
//	str_to_com.c
char    *cut_command(char *s, int *start, int *end);
char    **cut_all_commands(char *s, int *i);
t_command *get_commands_list(char **c);
char	**parse_command_args(char *command);
char	**free_strarray(char **s);
char	**ft_strtrim_array(char **s, char *set);
//end parsing
#endif
