#include "parser.h"

int	verify_content(t_token *tokens, int token_pos)
{
	if (tokens[token_pos].content == NULL)
	{
		clear_memory(tokens);
		return (0);
	}
	return (1);
}

void	move_str(int length, char *content, int *position, char *line)
{
	int	current;

	current = 0;
	while (current < length)
	{
		content[current] = line[*position + current];
		current++;
	}
	content[length] = END_OF_LINE;
}

void	skip_spaces(char *line, int *position)
{
	while ((line[*position] == SPACE || line[*position] == TAB) \
	&& line[*position] != END_OF_LINE)
		(*position)++;
}

int	get_quote_size(char *line, int *position, int quote)
{
	int	length;

	length = 0;
	while (line[*position + length] != quote \
	&& line[*position + length] != END_OF_LINE)
		length++;
	return (length);
}

int	get_word_size(char *line, int *position)
{
	int	length;

	length = 0;
	while (line[*position + length] != SPACE \
	&& line[*position + length] != TAB \
	&& line[*position + length] != QUOTE_SINGLE \
	&& line[*position + length] != QUOTE_DOUBLE \
	&& line[*position + length] != PIPE \
	&& line[*position + length] != RELINK_LEFT \
	&& line[*position + length] != RELINK_RIGHT \
	&& line[*position + length] != END_OF_LINE)
		length++;
	return (length);
}
