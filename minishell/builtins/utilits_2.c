#include "builtins.h"

// является ли строка валидныи именем переменной
int	ft_isvarchar_line(char *line)
{
	int	i;
	int	len;

	i = 0;
	if (line == NULL)
		return (0);
	len = ft_strlen(line);
	if (len == 0)
		return (0);
	if (line[0] >= '0' && line[0] <= '9')
		return (0);
	while (line[i])
	{
		if (ft_isvarchar(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

// подсчёт длины
int	ft_environ_len(void)
{
	int	i;

	i = 0;
	while (g_minishell.environ[i] != NULL)
		i++;
	return (i);
}

// поиск файла/папки
int	is_exist(char *path)
{
	struct stat	sb;

	if (!stat(path, &sb))
		return (1);
	return (0);
}

// подсчёт длины имени переменной
int	ft_export_name_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		i++;
	}
	return (i);
}

// подсчёт длины значения переменной
int	ft_export_value_len(char *line, int len_name)
{
	int	i;

	i = 0;
	len_name++;
	while (line[len_name])
	{
		len_name++;
		i++;
	}
	return (i);
}
