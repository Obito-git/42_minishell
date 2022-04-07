#include "expansion.h"

static char	*_next_any_quote(char *str)
{
	while (*str && !ft_is_in_set(*str, "\'\""))
		str++;
	return (str);
}

int	check_quotes(char *str)
{
	char	quote;

	//Use set_quote_mode to save lines
	if (*str == '\'' || *str == '\"')
		quote = *str;
	else
		quote = 0;
	while (*str)
	{
		if (quote == 0)
		{
			str = _next_any_quote(str);
			quote = *str;
		}
		else
		{
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == 0)
				return (-1);
			else
				quote = 0;
			str++;
		}
	}
	return (0);
}
