#include "parser.h"

int	get_tokens_size(t_token *tokens)
{
	int	position;

	position = 0;
	while (!tokens[position].last)
		position++;
	position++;
	return (position);
}

char	*get_content(t_token *tokens, int id)
{
	int	size;

	size = get_tokens_size(tokens);
	if (id < size && id > 0)
		return (tokens[id].content);
	return (NULL);
}

int	get_words(t_token *tokens, int id)
{
	int	size;

	size = get_tokens_size(tokens);
	if (id < size && id > 0)
		return (tokens[id].words);
	return (ERR_DEF);
}

int	get_quotes(t_token *tokens, int id)
{
	int	size;

	size = get_tokens_size(tokens);
	if (id < size && id > 0)
		return (tokens[id].quotes);
	return (ERR_DEF);
}

int	is_last(t_token *tokens, int id)
{
	int	size;

	size = get_tokens_size(tokens);
	if (id < size && id > 0)
		return (tokens[id].last);
	return (ERR_DEF);
}
