#include "parser.h"

void	select_value(char *content, char *content_new, \
int *position, char **variables)
{
	char	*value;

	if (content[*position] == DOLLAR && content[*position + 1] == QUESTION)
	{
		*position += 2;
		ft_straddback(content_new, g_minishell.error, 0, 0);
	}
	else if (content[*position] == DOLLAR && content[*position + 1] != DOLLAR \
		&& content[*position + 1] != END_OF_LINE)
	{
		value = get_variable(content, variables, position, 1);
		ft_straddback(content_new, value, 0, 1);
	}
	else
	{
		ft_straddback(content_new, &content[*position], 1, 0);
		(*position)++;
	}
}

char	*get_variable_name(char *content, int *position, int offset)
{
	int		length;
	int		current;
	char	*name;

	length = FOR_DOLLAR;
	current = 0;
	while (ft_isvarchar(content[*position + length]) \
	&& content[*position + length] != SPACE \
	&& content[*position + length] != TAB \
	&& content[*position + length] != DOLLAR \
	&& content[*position + length] != END_OF_LINE)
		length++;
	name = malloc(length + FOR_END_OF_LINE - FOR_DOLLAR);
	if (!name)
		ft_error_my_exit("malloc() error.\n", 42);
	while (current < length - FOR_DOLLAR)
	{
		name[current] = content[*position + current + FOR_DOLLAR];
		current++;
	}
	name[current] = END_OF_LINE;
	if (offset)
		(*position) += length;
	return (name);
}

char	*get_value_by_name(char *name, char **variables, int clear_memory)
{
	int		name_len;
	int		position;
	char	*value;

	value = NULL;
	if (!name || !variables)
		return (NULL);
	position = 0;
	name_len = ft_strlen(name);
	while (variables[position] != NULL)
	{
		if (ft_strlen(variables[position]) >= name_len \
		&& ft_strcmp(name, variables[position]) \
		&& (variables[position][name_len] == EQUAL \
		|| variables[position][name_len] == END_OF_LINE))
			value = ft_strcpy(variables[position] + name_len + FOR_EQUAL);
		if (value != NULL)
			break ;
		position++;
	}
	if (!value)
		value = ft_getstrempty();
	if (clear_memory)
		free(name);
	return (value);
}
