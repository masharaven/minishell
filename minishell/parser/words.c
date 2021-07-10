#include "parser.h"

char	*parse_quote(char *line, int *position, int *words, int *quotes)
{
	int		quote;
	int		length;
	char	*content;

	quote = line[(*position)++];
	length = get_quote_size(line, position, quote);
	content = malloc(length + FOR_END_OF_LINE);
	if (!content)
		ft_error_my_exit("malloc() error.\n", 42);
	move_str(length, content, position, line);
	*position += length + FOR_QUOTE;
	(*quotes)++;
	if (quote == QUOTE_DOUBLE)
		content = replace_variable(content, g_minishell.environ, 1);
	if (line[*position] == QUOTE_SINGLE || line[*position] == QUOTE_DOUBLE)
		content = ft_strjoin(content, parse_quote(line, \
		position, words, quotes), 1);
	else if (line[*position] == PIPE || line[*position] == RELINK_LEFT \
	|| line[*position] == RELINK_RIGHT)
		return (content);
	else if (line[*position] != SPACE && line[*position] != TAB \
	&& line[*position] != END_OF_LINE)
		content = ft_strjoin(content, parse_word(line, position, \
		words, quotes), 1);
	return (content);
}

char	*parse_word(char *line, int *position, int *words, int *quotes)
{
	int		length;
	char	*content;

	length = get_word_size(line, position);
	content = malloc(length + FOR_END_OF_LINE);
	if (!content)
		ft_error_my_exit("malloc() error.\n", 42);
	move_str(length, content, position, line);
	content[length] = END_OF_LINE;
	*position += length;
	(*words)++;
	content = replace_variable(content, g_minishell.environ, 1);
	if (line[*position] == QUOTE_SINGLE || line[*position] == QUOTE_DOUBLE)
		content = ft_strjoin(content, parse_quote(line, position, \
		words, quotes), 1);
	return (content);
}

char	*parse_special(char *line, int *position, int *words)
{
	int		length;
	int		current;
	char	*content;

	length = 0;
	current = 0;
	if (line[*position] == RELINK_RIGHT && line[*position + 1] == RELINK_RIGHT)
		length += 2;
	else if (line[*position] == RELINK_LEFT && line[*position + 1] \
	== RELINK_LEFT)
		length += 2;
	else
		length++;
	content = malloc(length + FOR_END_OF_LINE);
	if (!content)
		ft_error_my_exit("malloc() error.\n", 42);
	while (current < length)
	{
		content[current] = line[*position + current];
		current++;
	}
	content[length] = END_OF_LINE;
	(*position) += length;
	(*words)++;
	return (content);
}

char	*parse_block(char *line, int *position, int *words, int *quotes)
{
	if (line[*position] == QUOTE_SINGLE || line[*position] == QUOTE_DOUBLE)
		return (parse_quote(line, position, words, quotes));
	else if (line[*position] == PIPE || line[*position] == RELINK_LEFT \
	|| line[*position] == RELINK_RIGHT)
		return (parse_special(line, position, words));
	else
		return (parse_word(line, position, words, quotes));
}

char	*parse_blocks(char *line, t_token *tokens)
{
	int	token_pos;
	int	position;
	int	words;
	int	quotes;

	token_pos = 0;
	position = 0;
	while (line[position] != END_OF_LINE)
	{
		words = 0;
		quotes = 0;
		skip_spaces(line, &position);
		if (line[position] == END_OF_LINE)
			break ;
		tokens[token_pos].content = parse_block(line, &position, \
		&words, &quotes);
		tokens[token_pos].words = words;
		tokens[token_pos].quotes = quotes;
		if (!verify_content(tokens, token_pos))
			return (NULL);
		token_pos++;
	}
	return (line);
}
