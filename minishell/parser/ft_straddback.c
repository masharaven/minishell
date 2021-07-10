#include "parser.h"

void	clear_mem(char *str2, int clear_memory)
{
	if (clear_memory)
		free(str2);
}

char	*ft_straddback(char *str1, char *str2, int single_char, \
int clear_memory)
{
	int	str1_len;
	int	str2_len;
	int	position;

	if (!str1 || !str2)
		return (NULL);
	position = 0;
	str1_len = ft_strlen(str1);
	if (single_char)
	{
		str1[str1_len] = str2[0];
		str1[str1_len + 1] = END_OF_LINE;
	}
	else
	{
		str2_len = ft_strlen(str2);
		while (position < str2_len)
		{
			str1[str1_len + position] = str2[position];
			position++;
		}
		str1[str1_len + position] = END_OF_LINE;
	}
	clear_mem(str2, clear_memory);
	return (str1);
}
