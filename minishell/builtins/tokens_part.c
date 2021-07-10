#include "builtins.h"

// Длина от пайпа до пайпа
int	ft_tokens_count(t_token *tokens, int start)
{
	int	len;
	int	count;
	int	i;

	len = ft_tokens_len(tokens);
	count = 0;
	i = start;
	while (i < len)
	{
		if (ft_strncmp(tokens[start].content, "|") == 1)
			break ;
		start++;
		count++;
		i++;
	}
	return (count);
}

// Кол-во пайпов 
int	get_tokens_list_size(t_token *tokens)
{
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	while (!tokens[i].last)
	{
		if (ft_strncmp(tokens[i].content, "|") == 1)
			count_pipe++;
		if (ft_spec_char(tokens[i].content, tokens[i].quotes) \
		&& ft_spec_char(tokens[i + 1].content, tokens[i + 1].quotes))
			return (ERR_DEF);
		i++;
	}
	return (count_pipe);
}

// Кол-во пайпов с проверкой
int	get_tokens_list_size_check (t_token *tokens)
{
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	if (ft_strncmp(tokens[0].content, "|") && tokens[0].quotes == 0)
		return (global_error(SYNTAX_ERROR, 258, -1, tokens[0].content));
	while (!tokens[i].last)
	{
		if (size_body(tokens, i, &count_pipe) == -1)
			return (-1);
		i++;
	}
	if (ft_spec_char(tokens[i].content, tokens[i].quotes))
		return (global_error("ms: syntax error near unexpected token \
`newline'\n", 258, -1, NULL));
	if (ft_strncmp(tokens[i].content, "|") && tokens[0].quotes == 0)
		return (global_error(SYNTAX_ERROR, 258, -1, tokens[i].content));
	return (count_pipe);
}

// Копирует каждую часть набора токенов
void	check_pipe_p(t_token *tokens, t_token **tokens_list, int start, int i)
{
	int	tokens_list_len;
	int	j;

	tokens_list_len = ft_tokens_count(tokens, start);
	tokens_list[i] = malloc(sizeof(t_token) * tokens_list_len);
	if (tokens_list[i] == NULL)
		ft_error_my_exit("error malloc", 0);
	j = 0;
	while (j < tokens_list_len)
	{
		tokens_list[i][j].content = ft_strcpy(tokens[start + j].content);
		if (tokens_list[i][j].content == NULL)
			ft_error_my_exit("error malloc", 0);
		tokens_list[i][j].words = tokens[start + j].words;
		tokens_list[i][j].quotes = tokens[start + j].quotes;
		tokens_list[i][j].type = tokens[start + j].type;
		tokens_list[i][j].last = tokens[start + j].last;
		j++;
	}
	tokens_list[i][j - 1].last = 1;
}

// Делит токены на наборы токенов
//check_command(tokens_list[i]);
//printf("END_TEST\n");
t_token	**check_pipe(t_token *tokens)
{
	int		i;
	int		count_pipe;
	int		start;
	t_token	**tokens_list;
	int		tokens_list_l;

	count_pipe = get_tokens_list_size_check(tokens);
	if (count_pipe == -1)
		return (NULL);
	tokens_list = malloc(sizeof(t_token *) * (count_pipe + 1));
	if (tokens_list == NULL)
		ft_error_my_exit("error malloc", 0);
	i = 0;
	start = 0;
	while (i < (count_pipe + 1))
	{
		tokens_list_l = ft_tokens_count(tokens, start);
		check_pipe_p(tokens, tokens_list, start, i);
		start = start + tokens_list_l + 1;
		i++;
	}
	return (tokens_list);
}
