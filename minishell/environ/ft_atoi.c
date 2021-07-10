#include "environ.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		position;
	int		length;
	long	res;

	if (str[0] == '-')
		return (-1);
	length = ft_strlen(str);
	res = 0;
	position = 0;
	while (position < length)
	{
		if (!is_digit(str[position]))
			return (0);
		res = res * 10 + str[position] - '0';
		position++;
		if (res >= __INT_MAX__)
			return (0);
	}
	return (res);
}
