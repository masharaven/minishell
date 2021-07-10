#include "builtins.h"

// Возврат глобальнйо ошибки
// line - строку, которую нужно вывести
// err - номер ошибки, которую нужно поставить
// ret - значение функции, которое нужно возвратить
// token - строка, которая является ошибкой
int	global_error(char *line, int err, int ret, char *token)
{
	if (line != NULL)
		write(2, line, ft_strlen(line));
	if (token != NULL)
	{
		write(2, "`", 1);
		write(2, token, ft_strlen(token));
		write(2, "'\n", 2);
	}
	if (err == 0)
		g_minishell.error = "0";
	else if (err == 1)
		g_minishell.error = "1";
	else if (err == 2)
		g_minishell.error = "2";
	else if (err == 42)
		g_minishell.error = "42";
	else if (err == 127)
		g_minishell.error = "127";
	else if (err == 258)
		g_minishell.error = "258";
	return (ret);
}

// Возврат глобальной ошибки в другом виде
int	global_error_r(char *line, char *token, int err, int ret)
{
	if (line != NULL && token != NULL)
	{
		write(2, "ms: ", 4);
		write(2, line, ft_strlen(line));
		write(2, ": `", 3);
		write(2, token, ft_strlen(token));
		write(2, "': not a valid identifier\n", 27);
	}
	if (err == 0)
		g_minishell.error = "0";
	else if (err == 1)
		g_minishell.error = "1";
	else if (err == 2)
		g_minishell.error = "2";
	else if (err == 42)
		g_minishell.error = "42";
	else if (err == 127)
		g_minishell.error = "127";
	else if (err == 258)
		g_minishell.error = "258";
	return (ret);
}

void	global_exit(char *token, int code)
{
	if (token != NULL)
	{
		write (2, "ms: exit: ", 10);
		write (2, token, ft_strlen(token));
		write (2, ": numeric argument required\n", 29);
	}
	exit (code);
}

void	skipping_redirect(t_token *tokens)
{
	int	pos_rel;

	pos_rel = 0;
	while (!tokens[pos_rel].last)
	{
		if (ft_strncmp(tokens[pos_rel].content, "<<") && \
		tokens[pos_rel].quotes == 0)
		{
			relink_read_text(tokens[pos_rel + 1].content, 0);
		}
		pos_rel++;
	}
}

char	*redirect_data(t_token *tokens)
{
	char	*data;
	int		len;
	int		i;

	data = NULL;
	len = ft_tokens_len(tokens);
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(tokens[i].content, "<<") && tokens[i].quotes == 0)
		{
			if (data != NULL)
				free(data);
			data = relink_read_text(tokens[i + 1].content, 0);
		}
		else if (ft_strncmp(tokens[i].content, "<") && tokens[i].quotes == 0)
		{
			if (data != NULL)
				free(data);
			data = relink_read_file(tokens[i + 1].content);
		}
		i++;
	}
	return (data);
}
