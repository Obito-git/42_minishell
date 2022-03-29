#ifndef EXPANSION_H
#define EXPANSION_H

#include <assert.h>

#include "t_strlist.h"
#include <stdbool.h>

#define DOLLAR '$'
#define DOUBLE_QUOTE '\"'

enum e_expand_state {
	normal,
	var_start,
	in_var,
	done,
};

bool		is_special_var_start_char(int c);
bool		is_valid_shellvar_start_char(int c);
bool		is_valid_env_var_char(int c);
bool		is_single_dollar(char *c);
int			get_len_non_expandable_from_indexes(int *indexes);
int			get_expanded_len(t_strlist *exp_list, int *indexes);
t_strlist	*get_expansions_list(char *to_exp, int *indexes, t_strlist *env);
enum e_expand_state			normal_mode(char *str, int *i, int **indexes);;
enum e_expand_state			var_start_mode(char *str, int *i, int **indexes);;
enum e_expand_state			in_var_mode(char *str, int *i, int **indexes);;
int			next_var(char *str, int i);
int			next_non_env_var(char *str, int i);
//void		log_index(int i, int **table);
int			*register_expansions(char* to_exp);
char		*expand_arg(char *to_exp, int *indexes, t_strlist *env);
char		**expand_args(char **argv, t_strlist *env);

#endif /* EXPANSION_H */
