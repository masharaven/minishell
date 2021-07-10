#include "parser.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	position;

	position = 0;
	if (str1 == NULL || str2 == NULL)
		return (0);
	while (str1[position] != END_OF_LINE && str2[position] != END_OF_LINE)
	{
		if (str1[position] != str2[position])
			return (0);
		position++;
	}
	return (1);
}
