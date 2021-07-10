#include "parser.h"

int	get_variable_length(char *content, char **variables, \
int *position, int offset)
{
	int		length;
	char	*name;
	char	*value;

	name = get_variable_name(content, position, offset);
	value = get_value_by_name(name, variables, 1);
	length = ft_strlen(value);
	if (value != NULL)
		free(value);
	return (length);
}

int	get_content_length(char *content, char **variables)
{
	int	length;
	int	position;

	length = 0;
	position = 0;
	while (content[position] != END_OF_LINE)
	{
		if (content[position] == DOLLAR && content[position + 1] == QUESTION)
		{
			position++;
			length += ft_strlen(g_minishell.error);
		}
		else if (content[position] == DOLLAR && content[position + 1] != DOLLAR \
		&& content[position + 1] != END_OF_LINE)
			length += get_variable_length(content, variables, &position, 1);
		else
		{
			position++;
			length++;
		}
	}
	return (length);
}

char	*get_variable(char *content, char **variables, int *position, \
int offset)
{
	char	*name;
	char	*value;

	name = get_variable_name(content, position, offset);
	value = get_value_by_name(name, variables, 1);
	return (value);
}

char	*create_content(char *content, char **variables)
{
	int		length;
	int		position;
	char	*content_new;

	position = 0;
	length = get_content_length(content, variables);
	content_new = malloc(length + FOR_END_OF_LINE);
	if (!content_new)
		ft_error_my_exit("malloc() error.\n", 42);
	content_new[0] = END_OF_LINE;
	while (content[position] != END_OF_LINE)
		select_value(content, content_new, &position, variables);
	return (content_new);
}

char	*replace_variable(char *content, char **variables, int clear_memory)
{
	char	*new_content;

	if (!content)
		return (NULL);
	new_content = create_content(content, variables);
	if (clear_memory)
		free(content);
	return (new_content);
}
