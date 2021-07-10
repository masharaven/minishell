#include "other.h"

int	is_line_empty(char *line, int clear_mem)
{
	int	position;

	if (!line)
		return (1);
	position = 0;
	skip_spaces_t(line, &position);
	if (line[position] == END_OF_LINE)
	{
		if (clear_mem)
			free(line);
		return (1);
	}
	return (0);
}

void	ft_putstr(char *str)
{
	int	position;

	position = 0;
	while (str[position])
		position++;
	write(1, str, position);
}
