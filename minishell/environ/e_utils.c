#include "environ.h"

int	get_environ_size(char **env)
{
	int	position;

	position = 0;
	while (env != NULL && env[position] != NULL)
		position++;
	return (position);
}

int	environ_copy_line(char **env_new, int pos_new, int pos_old)
{
	env_new[pos_new] = ft_strcpy(g_minishell.environ[pos_old]);
	if (env_new[pos_new] == NULL)
	{
		environ_clear_memory_a(env_new, pos_new);
		return (0);
	}
	return (1);
}
