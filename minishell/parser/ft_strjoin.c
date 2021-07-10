#include "parser.h"

void	move_str1(char *str_new, char *str1, int str1_len)
{
	int	position;

	position = 0;
	while (position < str1_len)
	{
		str_new[position] = str1[position];
		position++;
	}
}

void	move_str2(char *str_new, char *str2, int str1_len, int str2_len)
{
	int	position;

	position = 0;
	while (position < str2_len)
	{
		str_new[str1_len + position] = str2[position];
		position++;
	}
}

int	check_null(char *str1, char *str2, int clear_memory)
{
	if (!str1 || !str2)
	{
		if (clear_memory && str1 != NULL)
			free(str1);
		if (clear_memory && str2 != NULL)
			free(str2);
		return (0);
	}
	return (1);
}

void	ft_strjoin_clear(char *str1, char *str2, int clear_memory)
{
	if (clear_memory)
	{
		free(str1);
		free(str2);
	}
}

char	*ft_strjoin(char *str1, char *str2, int clear_memory)
{
	int		str1_len;
	int		str2_len;
	char	*str_new;

	if (!check_null(str1, str2, clear_memory))
		return (NULL);
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	str_new = malloc(str1_len + str2_len + FOR_END_OF_LINE);
	if (!str_new)
		ft_error_my_exit("malloc() error.\n", 42);
	move_str1(str_new, str1, str1_len);
	move_str2(str_new, str2, str1_len, str2_len);
	str_new[str1_len + str2_len] = END_OF_LINE;
	ft_strjoin_clear(str1, str2, clear_memory);
	return (str_new);
}
