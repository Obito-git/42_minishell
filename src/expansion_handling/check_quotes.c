#include "expansion.h"

static char	*_next_any_quote(char *str)
{
	//Verify that this is correct
	while (*str && *str != '\'' && *str != '\"')
		str++;
	return (str);
}

int	check_quotes(char *str)
{
	char	quote;

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
