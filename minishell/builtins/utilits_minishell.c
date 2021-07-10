#include "builtins.h"

// Проверка на то, является ли строка спец символом
int	ft_spec_char(char *line, int quotes)
{
	if (ft_strncmp(line, "<") && quotes == 0)
		return (1);
	if (ft_strncmp(line, "<<") && quotes == 0)
		return (1);
	if (ft_strncmp(line, ">") && quotes == 0)
		return (1);
	if (ft_strncmp(line, ">>") && quotes == 0)
		return (1);
	if (ft_strncmp(line, "|") && quotes == 0)
		return (0);
	return (0);
}

// Подсчёт длины списка
int	ft_tokens_len(t_token *tokens)
{
	int	pos;

	pos = 0;
	while (!tokens[pos].last)
		pos++;
	pos++;
	return (pos);
}

// Вывод ошибки и возвращения 0
int	ft_error_my(char *line)
{
	write(2, line, ft_strlen(line));
	return (0);
}

// Вывод ошибки выход через exit с кодом
int	ft_error_my_exit(char *line, int num)
{
	if (line != NULL)
	{
		write(2, line, ft_strlen(line));
	}
	exit (num);
}

// Поведение при встрече спец символов
// printf("Заглушка\n");
int	ft_check_special_characters(int *pos, char *line)
{
	if (ft_strncmp(line, ">"))
		*pos = *pos + 1;
	else if (ft_strncmp(line, ">>"))
		*pos = *pos + 1;
	else if (ft_strncmp(line, "<"))
		*pos = *pos + 1;
	else if (ft_strncmp(line, "<<"))
	{
		*pos = *pos + 1;
	}
	else if (ft_strncmp(line, "|"))
		return (0);
	return (1);
}
