#include "builtins.h"

static int	ft_pas_arg_len(t_token *tokens);
static int	ft_pas_arg_rec(t_token tokens, char **argc_pass, int *j, int *log);

// Выбирает нужные аргументы для передачи
char	**ft_pas_arg_program(t_token *tokens, char **argc_pass)
{
	int	count_arg;
	int	len;
	int	i;
	int	j;
	int	log;

	i = 0;
	j = 0;
	log = 0;
	count_arg = ft_pas_arg_len(tokens);
	len = ft_tokens_len(tokens);
	argc_pass = malloc(sizeof(char *) * (count_arg + 2));
	if (argc_pass == NULL)
		ft_error_my_exit("Ошибка малока\n", 0);
	while (i < len)
		i += ft_pas_arg_rec(tokens[i], argc_pass, &j, &log);
	argc_pass[j] = NULL;
	return (argc_pass);
}

// Подсчитывает длину списка аргументов
static int	ft_pas_arg_len(t_token *tokens)
{
	int	count_arg;
	int	len;
	int	i;

	count_arg = 0;
	len = ft_tokens_len(tokens);
	i = 0;
	while (i < len)
	{
		if (ft_spec_char(tokens[i].content, tokens[i].quotes))
			ft_check_special_characters(&i, tokens[i].content);
		else
			count_arg++;
		i++;
	}
	return (count_arg);
}

// Записывает каждый аргумент
static int	ft_pas_arg_rec(t_token tokens, char **argc_pass, int *j, int *log)
{
	int	i;

	i = 0;
	if (ft_spec_char(tokens.content, tokens.quotes))
		ft_check_special_characters(&i, tokens.content);
	else
	{
		if (*log == 0)
		{
			argc_pass[*j] = cut_file_name(tokens.content, 0);
			if (argc_pass[*j] == NULL)
				ft_error_my_exit("Ошибка малока\n", 0);
			*log = 1;
		}
		else
		{
			argc_pass[*j] = ft_strdup(tokens.content);
			if (argc_pass[*j] == NULL)
				ft_error_my_exit("Ошибка малока\n", 0);
		}
		*j = *j + 1;
	}
	i++;
	return (i);
}

// Очищает двухмерный массив
void	ft_free_my(char **tab)
{
	int	position;

	position = 0;
	if (!tab)
		return ;
	while (tab[position] != NULL)
		free(tab[position++]);
	free(tab[position]);
	free(tab);
}

// Сравнивает первые n символов
int	ft_cmp_n(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	if (ft_strlen(str1) < n || ft_strlen(str2) < n)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
//printf("count_arg=%d\n", count_arg);
//---ТЕСТ
// i = 0;
// while (i < count_arg)
// {
// 	printf("(%s)\n", argc_pass[i]);
// 	i++;
// }
