#include "redirects.h"

void	create_new_line(char **new_line)
{
	*new_line = malloc(2);
	if (!*new_line)
		ft_error_my_exit("malloc() error.\n", 42);
	(*new_line)[0] = '\n';
	(*new_line)[1] = END_OF_LINE;
}

char	*add_text(char *line, char **text)
{
	char	*tmp;
	char	*new_line;
	char	*text_upd;

	if (*text == NULL)
		*text = line;
	else
	{
		create_new_line(&new_line);
		if (!new_line)
			return (NULL);
		tmp = ft_strjoin(*text, new_line, 1);
		if (!tmp)
			return (NULL);
		text_upd = ft_strjoin(tmp, line, 1);
		*text = text_upd;
	}
	return (*text);
}

char	*empty_validation(char *stop_str, int clear_stopstr_mem)
{
	if (!stop_str || is_line_empty(stop_str, 0))
	{
		if (clear_stopstr_mem)
			free(stop_str);
		return (NULL);
	}
	return (stop_str);
}

void	relink_exit(char *stop_str, int clear_stopstr_mem)
{
	if (clear_stopstr_mem)
		free(stop_str);
}

char	*relink_read_text(char *stop_str, int clear_stopstr_mem)
{
	char	*line;
	char	*text;

	text = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, stop_str) \
		&& ft_strlen(line) == ft_strlen(stop_str)))
		{
			if (line != NULL)
				free(line);
			relink_exit(stop_str, clear_stopstr_mem);
			if (text == NULL)
				return (ft_getstrempty());
			if (g_minishell.fd != NULL)
				dup2(*g_minishell.fd, STDOUT_FILENO);
			return (text);
		}
		if (add_text(line, &text) == NULL)
			exit(EXIT_FAILURE);
	}
}
