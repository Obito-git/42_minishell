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
	t_bool	pipe;
	char	in_mode;
	char	out_mode;
}	t_command;

//TESTING
void command_print(t_command *c);
//STRUCT_UTILS
t_command	*command_init(char *c, t_bool p, char in, char out);
void	free_command(t_command *c);
//PARSING
t_command *parse(char *com);
#endif
