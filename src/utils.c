#include "minishell.h"

bool is_pipe_redir(char *s)
{
    return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>")
            || !ft_strcmp(s, "<") || !ft_strcmp(s, "<<")
            || !ft_strcmp(s, "|"));
}