#include "builtins.h"

// Копирование n символов
void	ft_srtcopy_my(char *orig, char *copy, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		copy[i] = orig[i];
		i++;
	}
	copy[i] = '\0';
}

// Копирование начиная с n символа и до конца
void	ft_srtcopy_start_my(char *orig, char *copy, int start)
{
	int	i;

	i = 0;
	while (orig[start])
	{
		copy[i] = orig[start];
		i++;
		start++;
	}
	copy[i] = '\0';
}

// Сравнение n символов
int	ft_strncmp_my(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i == n)
		return (0);
	else
		return (s1[i] - s2[i]);
}

// Копирует начиная с определённой позиции
char	*ft_strcpy_start(char *str, int start)
{
	int		length;
	int		position;
	char	*str_new;

	if (!str)
		return (NULL);
	position = 0;
	length = ft_strlen(str);
	str_new = malloc(length - start + FOR_END_OF_LINE);
	if (!str_new)
		return (NULL);
	while (start < length)
	{
		str_new[position] = str[start];
		position++;
		start++;
	}
	str_new[position] = END_OF_LINE;
	return (str_new);
}

// проверяет сущетсвует ли файл
int	is_f_ex(char *path)
{
	struct stat	sb;

	if (!stat(path, &sb))
		return (S_ISREG(sb.st_mode));
	return (0);
}
