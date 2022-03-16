#include "minishell.h"

static const struct {
	char	*name;
	void	(*func)(void);
} s_built_in_table[] = {
	{"echo", NULL},
	{"cd", NULL},
	{"pwd", NULL},
	{"export", NULL},
	{"unset", NULL},
	{"env", NULL},
	{"exit", NULL},
};

void	(*get_built_in(t_command *cmd))(void)
{
	unsigned long	i;

	i = 0;
	while (i < sizeof(s_built_in_table)
		&& ft_strncmp(cmd->command,
			s_built_in_table[i].name,
			sizeof(s_built_in_table[i].name)))
	{
		i++;
	}
	if (i == sizeof(s_built_in_table))
		return (NULL);
	else
		return (s_built_in_table[i].func);
}
