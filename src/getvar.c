#include "minishell.h"

char	*getvar(char *var, char **envp)
{
	int vlen;

	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0)
			{
				return (*envp + vlen);
			}
			envp++;
		}
	}
	return (NULL);
}
