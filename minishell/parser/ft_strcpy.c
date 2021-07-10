#include "parser.h"

char	*ft_strcpy(char *str)
{
	int		length;
	int		position;
	char	*str_new;

	if (!str)
		return (NULL);
	position = 0;
	length = ft_strlen(str);
	str_new = malloc(length + FOR_END_OF_LINE);
	if (!str_new)
		ft_error_my_exit("malloc() error.\n", 42);
	while (position < length)
	{
		str_new[position] = str[position];
		position++;
	}
	str_new[position] = END_OF_LINE;
	return (str_new);
}
