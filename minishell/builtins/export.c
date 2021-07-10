#include "builtins.h"

static void	ft_export_record(t_token *tokens, t_builtins buil);
static int	ft_export_add(t_token *tokens, t_builtins buil);
static int	ft_export_add_check(char *line);

// Добавляет переменную
int	ft_export(t_token *tokens, t_builtins buil)
{
	int	len;
	int	pos;

	skipping_redirect(tokens);
	len = ft_tokens_len(tokens);
	pos = buil.pos + 1;
	while (pos < len)
	{
		if (ft_spec_char(tokens[pos].content, tokens[pos].quotes))
		{
			ft_check_special_characters(&pos, tokens[pos].content);
			pos++;
		}
		else
			break ;
	}
	if (len == pos)
		ft_export_record(tokens, buil);
	else
		return (ft_export_add(tokens, buil));
	return (global_error(NULL, 0, 1, NULL));
}

// Вывод отсортированного списка
static void	ft_export_record(t_token *tokens, t_builtins buil)
{
	int	file;

	if (buil.file_pos == -1)
		ft_tokens_sort(1);
	else
	{
		if (buil.recording_mode == 0)
			file = open(tokens[buil.file_pos].content, O_WRONLY);
		else
			file = open(tokens[buil.file_pos].content, O_WRONLY | O_APPEND);
		ft_tokens_sort(file);
		close(file);
	}
}

// Ищет список переменных для добавления
static int	ft_export_add(t_token *tokens, t_builtins buil)
{
	int	len;
	int	pos;
	int	log_err;
	int	temp;

	log_err = 0;
	len = ft_tokens_len(tokens);
	pos = buil.pos + 1;
	while (pos < len)
	{
		if (ft_spec_char(tokens[pos].content, tokens[pos].quotes))
			ft_check_special_characters(&pos, tokens[pos].content);
		else
		{
			temp = ft_export_add_check(tokens[pos].content);
			if (temp == 1)
				log_err = 1;
		}
		pos++;
	}
	return (global_error(NULL, log_err, 1, NULL));
}

// Добавляет переменную
static int	ft_export_add_check(char *line)
{
	char	*name;
	char	*value;
	int		len_name;
	int		len_value;

	len_name = ft_export_name_len(line);
	name = malloc(sizeof(char) * (len_name + 1));
	if (name == NULL)
		ft_error_my_exit("ms: error malloc\n", 0);
	ft_srtcopy_my(line, name, len_name);
	if (ft_isvarchar_line(name) == 0)
		return (global_error_r("export", name, 1, 1));
	if (line[len_name])
	{
		len_value = ft_export_value_len(line, len_name);
		value = malloc(sizeof(char) * (len_value + 1));
		if (value == NULL)
			ft_error_my_exit("ms: error malloc\n", 0);
		len_name++;
		ft_srtcopy_start_my(line, value, len_name);
		environ_add(name, value, 1, 1);
	}
	else
		environ_add(name, NULL, 1, 0);
	return (0);
}
