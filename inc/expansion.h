#ifndef EXPANSION_H
#define EXPANSION_H

#include <stdbool.h>

#include "libft.h"
#include "t_strlist.h"

#define DOLLAR '$'
#define DOUBLE_QUOTE '\"'

enum e_expand_state {
	normal,
	var_start,
	in_var,
	done,
};

enum e_quote_state {
	not_in_quote,
	single_quote,
	double_quote,
	fini,
};

//parsing
bool						is_special_var_start_char(int c);
bool						is_valid_shellvar_start_char(int c);
bool						is_valid_env_var_char(int c);
bool						is_single_dollar(char *c);

void						set_quote_mode(const char c, bool q[2]);

//Var registering modes
enum e_expand_state			normal_mode(char *str, int *i, int **indexes);
enum e_expand_state			var_start_mode(char *str, int *i, int **indexes);
enum e_expand_state			in_var_mode(char *str, int *i, int **indexes);

int							next_var(char *str, int i);
int							next_non_env_var(char *str, int i);
int							next_any_quote(char *str, int i);
int							next_double_quote(char *str, int i);
int							next_single_quote(char *str, int i);

void						log_index(int i, int **table);
int							*register_expansions(char* to_exp);
int							*register_quotes(char *str);

char						**expand_strings_depending_on_first_char(char **argv, t_strlist *env);
char						**quote_preserving_split(char *str);
char						*ft_join_null_terminated_str_array(char **str_array);
char						**split_on_unquoted_whitespace(char const *s, char *set);
char						**split_on_unquoted_redir(char const *s);
char						**expand_simple_command(char *simple_command, t_strlist *env);

int							check_quotes(char *str);
char						**handle_quotes(char **strarray);
char						**free_strarray(char **s);

enum e_quote_state	not_in_quote_mode(char *str, int *i, int **table);
enum e_quote_state	sq_mode(char *str, int *i, int **table);
enum e_quote_state	dq_mode(char *str, int *i, int **table);

#endif /* EXPANSION_H */
