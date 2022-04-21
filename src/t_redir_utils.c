#include "minishell.h"

t_redir	*new_redir()
{
	t_redir *new;

	new = (t_redir *) malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = NULL;
	new->mode = false;
	new->heredoc_fd = -1;
	new->next = NULL;
	return (new);
}

t_redir	*free_redir(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		free(head->filename);
		if (head->heredoc_fd != -1)
			close(head->heredoc_fd);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return (NULL);
}

t_redir	*append_redir(t_redir *head, char *mode, char *name)
{
	t_redir	*tmp;
	t_redir	*new;

	new = new_redir();
	if (!new)
		return (free_redir(head));
	new->filename = ft_strdup(name);
	if (!ft_strcmp(mode, ">>"))
		new->mode = OUT_APPEND;
	else if (!ft_strcmp(mode, ">"))
		new->mode = OUT_REWRITE;
	else if (!ft_strcmp(mode, "<"))
		new->mode = IN_FILE;
	else if (!ft_strcmp(mode, "<<")) 
		new->mode = IN_HEREDOC;
	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}