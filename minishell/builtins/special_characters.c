#include "builtins.h"

// обработка >
int	creat_file_redirect_out(t_token *tokens, int *file_pos, int pos)
{
	int	file;

	if (ft_strncmp(tokens[pos].content, ">") && tokens[pos].quotes == 0)
	{
		file = open(tokens[pos + 1].content, \
		O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		if (file == -1)
			return (global_error("ms: file not created", 42, 0, \
			tokens[pos + 1].content));
		*file_pos = pos + 1;
		close (file);
	}
	return (1);
}

// обработка >>
int	creat_file_redirect_out_mode(t_token *tokens, int *file_pos, int pos)
{
	int	file;

	if (ft_strncmp(tokens[pos].content, ">>") && tokens[pos].quotes == 0)
	{
		file = open(tokens[pos + 1].content, \
		O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		if (file == -1)
			return (global_error("ms: file not created", 42, 0, \
			tokens[pos + 1].content));
		*file_pos = pos + 1;
		close (file);
	}
	return (1);
}

// обработка <
int	creat_file_redirect_inp(t_token *tokens, int pos)
{
	if (ft_strncmp(tokens[pos].content, "<") && tokens[pos].quotes == 0)
	{
		if (is_exist(tokens[pos + 1].content) == 0)
		{
			write (2, "ms: ", 4);
			write (2, tokens[pos + 1].content, \
			ft_strlen(tokens[pos + 1].content));
			return (global_error(": No such file or directory\n", 1, 0, NULL));
		}
		else
			return (1);
	}
	return (1);
}

// обработка <<
int	creat_file_redirect_inp_mode(t_token *tokens, int pos)
{
	if (ft_strncmp(tokens[pos].content, "<<") && tokens[pos].quotes == 0)
	{
		return (1);
	}
	return (1);
}

// обрабокта |
int	ft_pipe(t_token *tokens, int pos)
{
	if (ft_strncmp(tokens[pos].content, "|") && tokens[pos].quotes == 0)
	{
		return (1);
	}
	return (1);
}
