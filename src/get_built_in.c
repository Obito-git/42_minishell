#include "minishell.h"

static const struct {
	char	*name;
	int		(*func)(void*, t_strlist *env);
} s_built_in_table[] = {
	{"echo", echo},
	{"cd", NULL},
	{"pwd", pwd},
	{"export", _export},
	{"unset", unset},
	{"env", NULL},
	{"exit", NULL},
};

int	(*get_built_in(t_command *cmd))(void*, t_strlist *)
{
	unsigned long	i;

	i = 0;
	while (i < sizeof(s_built_in_table)/sizeof(s_built_in_table[0]) - 1
		&& ft_strncmp(cmd->command,
			s_built_in_table[i].name,
			ft_strlen(cmd->command)))
	{
		i++;
	}
	if (i == sizeof(s_built_in_table))
		return (NULL);
	else
		return (s_built_in_table[i].func);
}
