#include "parser.h"

char	*parse_quote_t(char *line, int *position)
{
	int	quote;

	quote = line[*position];
	while (line[*position] != END_OF_LINE)
	{
		(*position)++;
		if (line[*position] == quote)
		{
			(*position)++;
			if (line[*position] == QUOTE_SINGLE \
			|| line[*position] == QUOTE_DOUBLE)
				parse_quote_t(line, position);
			else if (line[*position] == PIPE || line[*position] == RELINK_LEFT \
			|| line[*position] == RELINK_RIGHT)
				return (line);
			else if (line[*position] != SPACE && line[*position] != TAB \
			&& line[*position] != END_OF_LINE)
				parse_word_t(line, position);
			return (line);
		}
	}
	return (NULL);
}

char	*parse_word_t(char *line, int *position)
{
	while (line[*position] != SPACE && line[*position] != TAB \
	&& line[*position] != PIPE \
	&& line[*position] != RELINK_RIGHT && line[*position] != RELINK_LEFT \
	&& line[*position] != QUOTE_SINGLE && line[*position] != QUOTE_DOUBLE \
	&& line[*position] != END_OF_LINE)
		(*position)++;
	if (line[*position] == QUOTE_SINGLE || line[*position] == QUOTE_DOUBLE)
	{
		if (parse_quote_t(line, position) == NULL)
			return (NULL);
	}
	return (line);
}

void	parse_special_t(char *line, int *position)
{
	if (line[*position] == RELINK_RIGHT && line[*position + 1] == RELINK_RIGHT)
		(*position) += 2;
	else if (line[*position] == RELINK_LEFT \
	&& line[*position + 1] == RELINK_LEFT)
		(*position) += 2;
	else
		(*position)++;
}

char	*parse_element(char *line, int *position)
{
	if (line[*position] == QUOTE_SINGLE || line[*position] == QUOTE_DOUBLE)
	{
		if (parse_quote_t(line, position) == NULL)
			return (NULL);
	}
	else if (line[*position] == PIPE || line[*position] == RELINK_LEFT \
	|| line[*position] == RELINK_RIGHT)
		parse_special_t(line, position);
	else
	{
		if (parse_word_t(line, position) == NULL)
			return (NULL);
	}
	return (line);
}

int	get_tokens_count(char *line)
{
	int	count;
	int	position;

	count = 0;
	position = 0;
	while (line[position] != END_OF_LINE)
	{
		skip_spaces_t(line, &position);
		if (line[position] == END_OF_LINE)
			break ;
		if (parse_element(line, &position) == NULL)
			return (ERR_DEF);
		count++;
	}
	return (count);
}
