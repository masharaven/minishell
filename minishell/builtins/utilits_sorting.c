#include "builtins.h"

// Печать нужной строчки
static void	ft_tokens_sort_print(int min, int fd)
{
	int	len;
	int	i;
	int	log;

	len = ft_strlen(g_minishell.environ[min]);
	i = 0;
	log = 0;
	write(fd, "declare -x ", 11);
	while (i < len)
	{
		write(fd, &g_minishell.environ[min][i], 1);
		if (log == 0)
		{
			if (g_minishell.environ[min][i] == '=')
			{
				write(fd, "\"", 1);
				log = 1;
			}
		}
		i++;
	}
	if (log == 1)
		write(fd, "\"\n", 2);
	else
		write(fd, "\n", 1);
}

// сравнение строе
static int	e_cmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	if (str1[i] == '\0')
		return (-1);
	else if (str2[i] == '\0')
		return (1);
	return (0);
}

// ищет самое "минимальную" строку
static int	ft_tokens_sort_min(void)
{
	int	len;
	int	i;
	int	min;

	len = ft_environ_len();
	i = 0;
	min = 0;
	while (i < len)
	{
		if (e_cmp(g_minishell.environ[i], g_minishell.environ[min]) < 0)
			min = i;
		i++;
	}
	return (min);
}

// поиск очередной "минимальной" строки
static int	ft_tokens_sort_next(int str_pred)
{
	int	i;
	int	log;
	int	min;

	i = 0;
	log = 0;
	while (i < ft_environ_len())
	{
		if (e_cmp(g_minishell.environ[i], g_minishell.environ[str_pred]) > 0)
		{
			if (log == 0)
			{
				min = i;
				log = 1;
			}
			else
			{
				if (e_cmp(g_minishell.environ[i], g_minishell.environ[min]) < 0)
					min = i;
			}
		}
		i++;
	}
	return (min);
}

// вывод отсортированног осписка
void	ft_tokens_sort(int fd)
{
	int	len;
	int	min;
	int	str_pred;
	int	j;

	len = ft_environ_len();
	if (len == 0)
		return ;
	min = ft_tokens_sort_min();
	str_pred = min;
	j = 0;
	ft_tokens_sort_print(min, fd);
	while (j < (len - 1))
	{
		min = ft_tokens_sort_next(str_pred);
		ft_tokens_sort_print(min, fd);
		str_pred = min;
		j++;
	}
}
