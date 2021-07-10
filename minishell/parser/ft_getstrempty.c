#include "parser.h"

char	*ft_getstrempty(void)
{
	char	*str;

	str = malloc(FOR_END_OF_LINE);
	if (!str)
		ft_error_my_exit("malloc() error.\n", 42);
	str[0] = END_OF_LINE;
	return (str);
}
