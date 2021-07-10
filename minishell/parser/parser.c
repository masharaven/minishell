#include "parser.h"

t_token	*tokenize_line(char *line, int *error)
{
	int		count;
	t_token	*tokens;

	count = get_tokens_count(line);
	if (count == ERR_DEF)
	{
		*error = ERROR_NOT_CLOSED_QUOTE;
		return (NULL);
	}
	if (count == 0)
	{
		*error = ERROR_EMPTY_LINE;
		return (NULL);
	}
	if (initialize_tokens(&tokens, count) == NULL)
	{
		*error = ERROR_MALLOC;
		return (NULL);
	}
	if (parse_blocks(line, tokens) == NULL)
	{
		*error = ERROR_MALLOC;
		return (NULL);
	}
	return (tokens);
}
