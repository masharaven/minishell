#include "builtins.h"

static int	ft_start_com_rez(t_token *tokens, t_builtins buil, \
char *path, char *data);
static int	ft_sl(char *line);

// Запускает программу
int	ft_start_program(t_token *tokens, t_builtins buil)
{
	char	**argc_pass;
	int		rez;

	argc_pass = NULL;
	argc_pass = ft_pas_arg_program(tokens, argc_pass);
	if (argc_pass == NULL)
		ft_error_my_exit ("ms: error malloc\n", 0);
	if (buil.file_pos == -1)
		rez = process_run(argc_pass[0], argc_pass, NULL, buil.recording_mode);
	else
		rez = process_run(argc_pass[0], argc_pass, \
		tokens[buil.file_pos].content, buil.recording_mode);
	ft_free_my(argc_pass);
	if (rez == -1)
		return (global_error_dir(tokens[buil.pos].content));
	return (global_error(NULL, rez, 1, NULL));
}

static int	ft_start_command_path(t_token *tokens, t_builtins buil)
{
	int		rez;
	char	**argc_pass;

	argc_pass = NULL;
	argc_pass = ft_pas_arg_program(tokens, argc_pass);
	if (argc_pass == NULL)
		ft_error_my_exit ("ms: error malloc\n", 0);
	rez = process_run(tokens[buil.pos].content, argc_pass, \
	NULL, buil.recording_mode);
	ft_free_my(argc_pass);
	if (rez <= 0)
		return (global_error_dir(tokens[buil.pos].content));
	return (1);
}

int	ft_start_command(t_token *tokens, t_builtins buil)
{
	char	*path;
	char	*data;

	data = NULL;
	path = verify_binary_file(tokens[buil.pos].content, 0);
	data = redirect_data(tokens);
	if (path == NULL)
	{
		if (is_f_ex(tokens[buil.pos].content) && \
		ft_sl(tokens[buil.pos].content))
		{
			if (ft_start_command_path(tokens, buil) == 0)
			{
				free (data);
				return (0);
			}
		}
		else
		{
			free (data);
			return (global_error_com(tokens[buil.pos].content));
		}
	}
	return (ft_start_com_rez(tokens, buil, path, data));
}

static int	ft_start_com_rez(t_token *tokens, t_builtins buil, \
char *path, char *data)
{
	int				rez;
	char			**argc_pass;
	t_relink_info	relink_info;

	relink_info.relink_path = NULL;
	if (buil.file_pos != -1)
		relink_info.relink_path = tokens[buil.file_pos].content;
	relink_info.write_mode = buil.recording_mode;
	argc_pass = NULL;
	argc_pass = ft_pas_arg_program(tokens, argc_pass);
	if (argc_pass == NULL)
		ft_error_my_exit ("ms: error malloc\n", 0);
	rez = process_run_smart(path, argc_pass, relink_info, data);
	ft_free_my(argc_pass);
	free(path);
	free(data);
	if (rez == -1)
		return (global_error_dir(tokens[buil.pos].content));
	return (global_error(NULL, rez, 1, NULL));
}

// Поиск /, но не на 1 позиции и не не последней
static int	ft_sl(char *line)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(line);
	while (i < (len - 1))
	{
		if (line[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
