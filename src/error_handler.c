#include "minishell.h"

t_command   *find_syntax_errors(t_command *head)
{
    char        *msg;
    t_command   *last;

    last = head;
    while (last->next)
        last = last->next;
    if (ft_strlen(head->command) == 0 && head->pipe)
        msg = "minishell: syntax error near unexpected token `|'\n";
    else if (last->out_mode)
        msg = "minishell: syntax error near unexpected token `newline'\n";
    else
        return (head);
    ft_putstr_fd(msg, 2);
    free_commands(head);
    return (NULL);
}