#include "builtins.h"

// Является ли строка числом
int	ft_number_my(char *str)
{
	int	i;

	i = 0;
	if ((ft_strlen(str) == 1) && (str[0] == '-'))
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

// перевод в str в int c проверкой на переполнение
int	ft_atoi_my(const char *str, int *value)
{
	long long int	num;
	int				zn;
	int				i;

	zn = 0;
	num = 0;
	i = 0;
	if (str[i] == '-')
	{
		zn = 1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + str[i] - 48;
		if ((num > 2147483647) && (zn == 0))
			return (0);
		if ((num > 2147483648) && (zn == 1))
			return (0);
		i++;
	}
	if (zn == 1)
		num = num * (-1);
	*value = num;
	return (1);
}

// Соединение строк
// space --> надо ли в конец пробел добавлять(1 - да, 0 - нет)
char	*ft_strjoin_my(char *s1, char *s2, int space)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*new_str;

	if (!s1 || !s2)
		ft_error_my_exit("malloc error", 0);
	i = -1;
	j = 0;
	size = (ft_strlen(s1) + ft_strlen(s2) + 1 + space) * (sizeof(*s1));
	new_str = (char *)malloc(size);
	if (new_str == NULL)
		ft_error_my_exit("malloc error", 0);
	while (s1[++i])
		new_str[i] = s1[i];
	if (space == 1)
		new_str[i + j] = ' ';
	while (s2[j])
	{
		new_str[i + j + space] = s2[j];
		j++;
	}
	new_str[i + j + space] = '\0';
	free(s1);
	return (new_str);
}

// Полное сравнение строк
int	ft_strncmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

// Выделяет память под строку
char	*ft_strdup(char *s1)
{
	int		i;
	int		s;
	char	*new_str;

	i = ft_strlen(s1);
	s = 0;
	new_str = (char *)malloc(sizeof(new_str) * (i + 1));
	if (!(s1) || new_str == NULL)
		return (NULL);
	while (s1[s])
	{
		new_str[s] = s1[s];
		s++;
	}
	new_str[s] = '\0';
	return (new_str);
}
