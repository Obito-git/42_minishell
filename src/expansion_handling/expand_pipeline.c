#include "minishell.h"

//Expansion covers quote handling and variable replacement
t_strlist	*expand_pipeline(char *user_input, t_strlist *env)
{
	char		**pipeline;
	char		**simple_cmd;
	int			i;
	t_strlist	*arg_list;

	arg_list = new_strlist();
	if (!arg_list)
		return (NULL);
	pipeline = split_on_unquoted_redir(user_input, ">|<");
	i = 0;
	while (pipeline && pipeline[i])
	{
		simple_cmd = expand_simple_command(pipeline[i], env);
		if (!simple_cmd || append_strarray_to_strlist(arg_list, simple_cmd))
		{
			free_strarray(pipeline);
			free_strlist(arg_list);
			return (NULL);
		}
		free_strarray(simple_cmd);
		i++;
	}
	free_strarray(pipeline);
	return (arg_list);
}
