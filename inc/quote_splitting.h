#ifndef QUOTE_SPLITTING_H
#define QUOTE_SPLITTING_H

//Erase
#include <assert.h>
#include <string.h>
#include <stdio.h>
//Erase this above !

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

#endif /* QUOTE_SPLITTING_H */
