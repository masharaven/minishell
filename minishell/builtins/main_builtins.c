#include "builtins.h"

static int	command_start(t_token *tokens, int *file_pos, int *recording_mode);
static int	creat_file(t_token *tokens, int	*file_pos);
static int	rec_mode_file(t_token *tokens, int *file_pos, int *recording_mode);
static int	check_command_my(t_token *tokens, t_builtins	buil);

// Если первый аргумент, это валидная команда, то запустим её
int	check_command(t_token *tokens)
{
	t_builtins	buil;
	int			len;

	buil.file_pos = -1;
	buil.recording_mode = -1;
	buil.pos = 0;
	len = ft_tokens_len(tokens);
	if (command_start(tokens, &buil.file_pos, &buil.recording_mode) == 0)
		return (0);
	while (buil.pos < len)
	{
		if (ft_spec_char(tokens[buil.pos].content, tokens[buil.pos].quotes))
			ft_check_special_characters(&buil.pos, tokens[buil.pos].content);
		else
			return (check_command_my(tokens, buil));
		buil.pos++;
	}
	return (1);
}

// Проверяет валидна ли последовательнсоть аргументов
static	int	command_start(t_token *tokens, int *file_pos, int *recording_mode)
{
	int	len;
	int	pos;

	len = ft_tokens_len(tokens);
	pos = 0;
	while (!tokens[pos].last)
	{
		if (ft_spec_char(tokens[pos].content, tokens[pos].quotes) \
		&& ft_spec_char(tokens[pos + 1].content, tokens[pos + 1].quotes))
			return (global_error("ms: syntax error near unexpected token ", \
			258, 0, tokens[pos + 1].content));
		pos++;
	}
	if (ft_spec_char(tokens[pos].content, tokens[pos].quotes))
		return (global_error("ms: syntax error near unexpected token \
`newline'\n", 258, 0, NULL));
	if (creat_file(tokens, file_pos) == 0)
		return (0);
	rec_mode_file(tokens, file_pos, recording_mode);
	return (1);
}

// Ищет команды
static int	check_command_my(t_token *tokens, t_builtins buil)
{
	if (ft_strncmp(tokens[buil.pos].content, "echo"))
		return (ft_echo(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "cd"))
		return (ft_cd(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "pwd"))
		return (ft_pwd(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "export"))
		return (ft_export(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "unset"))
		return (ft_unset(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "env"))
		return (ft_env(tokens, buil));
	else if (ft_strncmp(tokens[buil.pos].content, "exit"))
		return (ft_exit(tokens, buil));
	else if (ft_cmp_n(tokens[buil.pos].content, "./", 2))
		return (ft_start_program(tokens, buil));
	else
		return (ft_start_command(tokens, buil));
	return (1);
}

// Создаются нужные файлы и проверяются существующие
static	int	creat_file(t_token *tokens, int	*file_pos)
{
	int	len;
	int	pos;

	len = ft_tokens_len(tokens);
	pos = 0;
	if (len < 2)
		return (1);
	while (!tokens[pos].last)
	{
		if (creat_file_redirect_out(tokens, file_pos, pos) == 0)
			return (0);
		if (creat_file_redirect_out_mode(tokens, file_pos, pos) == 0)
			return (0);
		if (creat_file_redirect_inp(tokens, pos) == 0)
			return (0);
		if (creat_file_redirect_inp_mode(tokens, pos) == 0)
			return (0);
		if (ft_pipe(tokens, pos) == 0)
			return (0);
		pos++;
	}
	return (1);
}

// Определяется режим записи в файл
static int	rec_mode_file(t_token *tokens, int *file_pos, int *recording_mode)
{
	int	pos;

	pos = 1;
	if (ft_tokens_len(tokens) < 3 || *file_pos == -1)
		return (1);
	while (!tokens[pos].last)
	{
		if (ft_strncmp(tokens[pos].content, ">") && tokens[pos].quotes == 0)
		{
			if (ft_strncmp(tokens[pos + 1].content, tokens[*file_pos].content))
				*recording_mode = 0;
		}
		else if (ft_strncmp(tokens[pos].content, ">>") \
		&& tokens[pos].quotes == 0)
		{
			if (ft_strncmp(tokens[pos + 1].content, tokens[*file_pos].content))
			{
				if (*recording_mode == -1)
					*recording_mode = 1;
			}
		}
		pos++;
	}
	return (1);
}
