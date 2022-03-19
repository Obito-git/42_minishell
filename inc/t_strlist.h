#ifndef T_STRLIST_H
#define T_STRLIST_H

#include <stddef.h>

typedef struct s_strlist_node {
	char	*str;
	struct s_strlist_node *next;
	struct s_strlist_node *prev;
}	t_strlist_node;

typedef struct s_strlist {
	t_strlist_node	*head;
	size_t			size;
	char			**envp;
} t_strlist;

t_strlist		init_strlist();
t_strlist		*new_strlist();
t_strlist_node	init_strlist_node();
t_strlist_node *new_strlist_node();
void			deinit_strlist(t_strlist *list);
void			free_strlist(t_strlist *list);
void			append_node_to_strlist(t_strlist *list, t_strlist_node *node);
int				append_str_to_strlist(t_strlist *list, char *str);
void			remove_node_from_strlist(t_strlist *list, t_strlist_node *node);
void			remove_str_from_strlist(t_strlist *list, char *str);
t_strlist		*make_strlist_from_null_terminated_str_array(char **envp);

#endif /* T_STRLIST_H */
