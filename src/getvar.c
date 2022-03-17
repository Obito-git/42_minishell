#include "minishell.h"

char	*getvar(char *var, char **envp)
{
	int	vlen;

	var++;
	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0)
			{
				return (*envp + vlen + 1);
			}
			envp++;
		}
	}
	return (NULL);
}

ssize_t	writevar(int fd, char *var, char **envp)
{
	size_t	len;

	var = getvar(var, envp);
	len = ft_strlen(var);
	return (write(fd, var, len));
}
