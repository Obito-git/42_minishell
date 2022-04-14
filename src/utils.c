#include "minishell.h"

int isDirectory(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

bool is_pipe_redir(char *s)
{
    return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>")
            || !ft_strcmp(s, "<") || !ft_strcmp(s, "<<")
            || !ft_strcmp(s, "|"));
}