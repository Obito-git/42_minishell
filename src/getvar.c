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

char	*get_env_var_val_from_slice(char *var, char *var_end, t_strlist *env)
{
	int	vlen;
	char	**envp;

	if (var && *var != '$')
		return (NULL);
	var++;
	envp = env->strarr_value;
	vlen = var_end - var;
	if (envp)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, var, vlen) == 0
				&& *(*envp + vlen) == '=' )
				return (ft_strdup(*envp + vlen + 1));
			envp++;
		}
	}
	if (!ft_strcmp("?", var))
		return ft_itoa(env->ret);
	return (NULL);
}
