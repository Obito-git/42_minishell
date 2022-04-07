#include "expansion.h"

/* Goes to next dollar that is not a single dollar */
int	next_var(char *str, int i)
{
	while (str[i] && (is_single_dollar(&str[i]) || str[i] != DOLLAR))
		i++;
	return (i);
}

/* Does not account for $ or any special char */
int	next_non_env_var(char *str, int i)
{
	while (is_valid_env_var_char(str[i]))
		i++;
	return (i);
}

