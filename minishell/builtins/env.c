#include "builtins.h"

static void	ft_env_print(int fd);

//печатает список переменных
int	ft_env(t_token *tokens, t_builtins buil)
{
	int	file;

	skipping_redirect(tokens);
	if (buil.file_pos == -1)
		ft_env_print(1);
	else
	{
		if (buil.recording_mode == 0)
			file = open(tokens[buil.file_pos].content, O_WRONLY);
		else
			file = open(tokens[buil.file_pos].content, O_WRONLY | O_APPEND);
		ft_env_print(file);
		close(file);
	}
	return (global_error(NULL, 0, 1, NULL));
}

// Выводит на экран список переменных
static void	ft_env_print(int fd)
{
	int	i;

	i = 0;
	while (g_minishell.environ[i] != NULL)
	{
		write(fd, g_minishell.environ[i], ft_strlen(g_minishell.environ[i]));
		write(fd, "\n", 1);
		i++;
	}
}
