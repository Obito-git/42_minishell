#include "minishell.h"

char	*get_env_var_start(char *var, char **envp)
{
	int	vlen;

	var++;
	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
			{
				return (*envp);
			}
			envp++;
		}
	}
	return (NULL);
}

char	*get_env_var_val(char *var, char **envp)
{
	int	vlen;

	var++;
	vlen = ft_strlen(var);
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
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

	var = get_env_var_val(var, envp);
	len = ft_strlen(var);
	return (write(fd, var, len));
}
