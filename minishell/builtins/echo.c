#include "builtins.h"

static int	ft_echo_init(t_token *tokens, int *pos, int *mode, int *log_read);
static int	ft_echo_mode(t_token *tokens, int *pos);
static void	ft_echo_rec(t_token *tokens, t_builtins buil, char *line, int mode);

// Вывод текста 
int	ft_echo(t_token *tokens, t_builtins buil)
{
	int		mode;
	char	*line;
	int		log_read;

	skipping_redirect(tokens);
	if (ft_echo_init(tokens, &buil.pos, &mode, &log_read) == 1)
		return (global_error(NULL, 0, 1, NULL));
	line = ft_strdup("\0");
	if (line == NULL)
		ft_error_my_exit ("ms: error malloc\n", 0);
	while (buil.pos < ft_tokens_len(tokens))
	{
		if (ft_spec_char(tokens[buil.pos].content, tokens[buil.pos].quotes))
			ft_check_special_characters(&buil.pos, tokens[buil.pos].content);
		else
		{
			line = ft_strjoin_my(line, tokens[buil.pos].content, log_read);
			if (line == NULL)
				ft_error_my_exit ("ms: error malloc\n", 0);
			log_read = 1;
		}
		buil.pos++;
	}
	ft_echo_rec(tokens, buil, line, mode);
	return (global_error(NULL, 0, 1, NULL));
}

// Предобработка
static int	ft_echo_init(t_token *tokens, int *pos, int *mode, int *log_read)
{
	int	len;

	*log_read = 0;
	len = ft_tokens_len(tokens);
	if (len == 1)
	{
		printf("\n");
		return (1);
	}
	*pos = *pos + 1;
	*mode = ft_echo_mode(tokens, pos);
	if (*pos == len)
		return (1);
	return (0);
}

// Определяет включена ли опция -n
static int	ft_echo_mode(t_token *tokens, int *pos)
{
	int	mode;

	mode = 0;
	while (!tokens[*pos].last)
	{
		if (ft_strncmp(tokens[*pos].content, "-n") == 1)
		{
			mode = 1;
			*pos = *pos + 1;
			continue ;
		}
		else
			break ;
	}
	if (ft_strncmp(tokens[*pos].content, "-n") == 1)
		mode = 1;
	return (mode);
}

// Выводим данные в нужное место
static void	ft_echo_rec(t_token *tokens, t_builtins buil, char *line, int mode)
{
	int	file;

	if (buil.file_pos == -1)
	{
		file = 1;
		if (mode == 0)
			printf("%s\n", line);
		else
			printf("%s", line);
	}
	else
	{
		if (buil.recording_mode == 0)
			file = open(tokens[buil.file_pos].content, O_WRONLY);
		else
			file = open(tokens[buil.file_pos].content, O_WRONLY | O_APPEND);
		write(file, line, ft_strlen(line));
		if (mode == 0)
			write(file, "\n", 1);
		close(file);
	}
	free(line);
}
