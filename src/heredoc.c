#include "minishell.h"

//heredoc readline funtion.
char    *read_heredoc_mode(char *delim)
{
	char	*res;
	char	*current_line;
	char	*tmp;

 	res = readline("> ");
 	if (!res || !ft_strcmp(res, delim))
 	{
 		free(res);
		return (NULL);
	}
	while(res)
	{
		current_line = readline("> ");
		tmp = ft_strjoin(res, "\n");
		free(res);
		if (!current_line || !ft_strcmp(current_line, delim))
		{
			free(current_line);
			return (tmp);
		}
		res = ft_strjoin(tmp, current_line);
		free(current_line);
		free(tmp);
	}
	return (res);
}

//generete name for tmp file depending on the position of the structure in the list
char	*get_heredoc_tmpname(t_command *head, t_command *current)
{
	char	*filename;
	char	*numb;
	char	*tmp;
	int		id;

	id = 0;
	filename = ft_strdup(".tmpheredoc");
	while (head && head != current)
	{
		id++;
		head = head->next;
	}
	tmp = filename;
	numb = ft_itoa(id);
	filename = ft_strjoin(filename, numb);
	free(tmp);
	free(numb);
	return (filename);
}

//reads content in heredoc mode and saves it in hidden tmp file.
int		get_heredoc_fd(char *delim, t_command *head, t_command *current)
{
	char	*content;
	char	*filename;
	int		fd;

	content = read_heredoc_mode(delim);
	filename = get_heredoc_tmpname(head, current);
	if (!filename)
	{
		free(content);
		return (0);
	}
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644); //prot
	write(fd, content, ft_strlen(content));
	close(fd);
	fd = open(filename, O_RDONLY);
	free(content);
	free(filename);
	return (fd);
}