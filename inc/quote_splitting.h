#ifndef QUOTE_SPLITTING_H
#define QUOTE_SPLITTING_H
#include "minishell.h"

enum e_quote_state {
	not_in_quote,
	single_quote,
	double_quote,
	fini,
};

enum e_quote_state	not_in_quote_mode(char *str, int *i, int **table);
enum e_quote_state	sq_mode(char *str, int *i, int **table);
enum e_quote_state	dq_mode(char *str, int *i, int **table);
int					next_any_quote(char *str, int i);
int					next_double_quote(char *str, int i);
int					next_single_quote(char *str, int i);
int					*register_quotes(char *str);
int					check_quotes(char *str);
char				**quote_preserving_split_splitter(char *str, int *index_table);
char				**quote_preserving_split(char *str);
char				**split_on_unquoted_whitespace(char const *s, char *set);
char				**handle_quotes(char **strarray);

#endif /* QUOTE_SPLITTING_H */
