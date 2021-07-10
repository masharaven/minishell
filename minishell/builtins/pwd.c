#include "builtins.h"

// Показывает текущую директорию
int	ft_pwd(t_token *tokens, t_builtins buil)
{
	char	cwd[1024];
	int		file;
	int		i;

	skipping_redirect(tokens);
	getcwd(cwd, 1024);
	i = 0;
	if (buil.file_pos == -1)
		printf("%s\n", cwd);
	else
	{
		if (buil.recording_mode == 0)
			file = open(tokens[buil.file_pos].content, O_WRONLY);
		else
			file = open(tokens[buil.file_pos].content, O_WRONLY | O_APPEND);
		write(file, cwd, ft_strlen(cwd));
		write(file, "\n", 1);
		close(file);
	}
	return (global_error(NULL, 0, 1, NULL));
}
