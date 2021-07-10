#include "parser.h"

int 	ft_strlen(char *str)
{
	int	position;

	if (!str)
		return (0);
	position = 0;
	while (str[position] != END_OF_LINE)
		position++;
	return (position);
}
