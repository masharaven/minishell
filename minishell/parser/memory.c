#include "parser.h"

t_token	**initialize_tokens(t_token **tokens, int size)
{
	int	position;

	position = 0;
	*tokens = malloc(sizeof(t_token) * (size));
	if (!*tokens)
		ft_error_my_exit("malloc() error.\n", 42);
	while (position < size)
	{
		(*tokens)[position].content = NULL;
		(*tokens)[position].words = 0;
		(*tokens)[position].quotes = 0;
		(*tokens)[position].type = 0;
		(*tokens)[position].last = 0;
		if (position == size - 1)
			(*tokens)[position].last = 1;
		position++;
	}
	return (tokens);
}

void	clear_memory(t_token *tokens)
{
	int	size;
	int	position;

	size = get_tokens_size(tokens);
	position = 0;
	while (position < size)
	{
		if (tokens[position].content != NULL)
			free(tokens[position].content);
		position++;
	}
	free(tokens);
}
