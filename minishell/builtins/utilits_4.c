#include "builtins.h"

void	check_pipe_free(t_token	**tokens_list, int count_tok)
{
	int	i;
	int	j;

	i = 0;
	while (i < count_tok)
	{
		j = 0;
		while (!tokens_list[i][j].last)
		{
			free(tokens_list[i][j].content);
			j++;
		}
		free(tokens_list[i][j].content);
		free(tokens_list[i]);
		i++;
	}
	free(tokens_list);
}

int	global_error_dir(char *line)
{
	write (2, "ms: ", 4);
	write (2, line, ft_strlen(line));
	write (2, ": No such file or directory\n", 29);
	g_minishell.error = "1";
	return (0);
}

int	global_error_com(char *line)
{
	write (2, "ms: ", 4);
	write (2, line, ft_strlen(line));
	write (2, ": command not found\n", 21);
	g_minishell.error = "127";
	return (0);
}

int	size_body(t_token *tokens, int i, int *count_pipe)
{
	if (ft_strncmp(tokens[i].content, "|") && tokens[i].quotes == 0)
		*count_pipe = *count_pipe + 1;
	if (ft_strncmp(tokens[i].content, "|") && tokens[i].quotes == 0 \
	&& ft_spec_char(tokens[i - 1].content, tokens[i - 1].quotes))
		return (global_error(SYNTAX_ERROR, 258, -1, tokens[i].content));
	if (ft_spec_char(tokens[i].content, tokens[i].quotes) \
	&& ft_spec_char(tokens[i + 1].content, tokens[i + 1].quotes))
		return (global_error(SYNTAX_ERROR, 258, -1, tokens[i + 1].content));
	if (ft_strncmp(tokens[i].content, "|") \
	&& ft_strncmp(tokens[i + 1].content, "|") \
	&& tokens[i].quotes == 0 && tokens[i + 1].quotes == 0)
		return (global_error(SYNTAX_ERROR, 258, -1, tokens[i + 1].content));
	return (1);
}

// Поведение при встрече спец символов
// printf("Заглушка\n");
int	ft_check_special_characters_mode(int *pos, char *line)
{
	if (ft_strncmp(line, ">"))
		*pos = *pos + 1;
	else if (ft_strncmp(line, ">>"))
		*pos = *pos + 1;
	else if (ft_strncmp(line, "<"))
		*pos = *pos + 0;
	else if (ft_strncmp(line, "<<"))
	{
		*pos = *pos + 1;
	}
	else if (ft_strncmp(line, "|"))
		return (0);
	return (1);
}
