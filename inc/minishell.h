#ifndef MINISHELL_H
#define MINISHELL_H

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
# include <signal.h>
# include <sys/signal.h>
# include "libft.h"
# include "t_strlist.h"
# include "expansion.h"
# include "quote_splitting.h"
# ifndef PATH_MAX
	# define PATH_MAX 4096
# endif
# define OUT_REWRITE 1
# define OUT_APPEND 2
# define IN_FILE 1
# define IN_HEREDOC 2
# define _GNU_SOURCE 1
# define EXIT_UNK_CMD 127

# define RED   "\e[31m"
# define ENDCOLOR   "\e[0m "
# define PROMPT   "\e[2K\e[G" RED "minishell$" ENDCOLOR
# define REPROMPT   "\n\e[31mminishell$\e[0m "

# define ERROR_SYNTAX "syntax error near unexpected token "
# define HEADER "minishell: "

#define DOLLAR '$'
#define DOUBLE_QUOTE '\"'

typedef struct sigaction t_sigaction;

typedef struct s_command
{
	char	*command;
	char	*path_to_bin;
	char	**args;
	bool	pipe;
	char	in_mode;
	char	out_mode;
	int		*tube;
	struct s_command *next;
	struct s_command *prev;
}	t_command;

typedef struct s_inout_fd
{
	int	in_fd;
	int out_fd;
}	t_inout_fd;

//	struct_utils.c
t_command	*command_init(void);
t_command	*free_commands(t_command *c);
t_command	*get_last_cmd(t_command *head);
//	parsing
bool		is_pipe_redir(char c);
char		*find_command(char **envp, t_command *c);
t_command	*parse(char *user_input, t_strlist *env);
//	str_to_struct.c
t_command *get_commands_list(char **c, t_strlist *env);
//	utils.c
char		**free_strarray(char **s);
char		**ft_strtrim_array(char **s, char *set);
char	*ft_join_null_terminated_str_array(char **str_array);
void	print_strarray(char **com);
bool	ft_is_in_set(char c, char *set);
char	*ft_strcat_slice(char *dest, const char *src, int n);
char	**split_on_unquoted_redir(char const *s, char *set);
//	executor.c
void		close_extra_tubes(t_command *head, t_command *current);
int			execute_pipeline(t_command *head, t_strlist *env);
//	pipes_redir.c
t_inout_fd *set_redirections(t_command *c, t_command *head, t_strlist *env);
void		set_tubes_path(t_command *head, t_command *c);
void		close_fds(t_inout_fd *fds);
//	error_handler.c
t_command   *find_syntax_errors(t_command *head, t_strlist *env);
//	heredoc.c
int		get_heredoc_fd(char *delim, t_command *head, t_command *current);
char	*get_heredoc_tmpname(t_command *head, t_command *current);
//built-ins
int	(*get_built_in(t_command *cmd))(t_command *cmd, t_strlist *env);
int	echo(t_command *cmd, t_strlist *env);
int	pwd(t_command *cmd, t_strlist *env);
int	unset(t_command *cmd, t_strlist *env);
int	xport(t_command *cmd, t_strlist *env);
int	xit(t_command *cmd, t_strlist *env);
int	env(t_command *cmd, t_strlist *env);
int	cd(t_command *cmd, t_strlist *env);
//env
char	*get_env_var_start(char *var, char **envp);
char	*get_env_var_val(char *var, char **envp);
ssize_t	writevar(int fd, char *var, char **envp);
//vars
char	*get_env_var_val_from_slice(char *var, char *var_end, t_strlist *env);
// signal handling
void	set_signal_handling();
void	sigint_handler(int signal);
void	sigquit_handler(int signal);
void	reset_signals();
void	reset_sigint();
void	reset_sigquit();
#endif
