#include "environ.h"

void	environ_clear_memory_a(char **env, int size)
{
	int	position;

	if (!env)
		return ;
	position = 0;
	while (position < size)
		free(env[position++]);
	free(env);
}

char	**environ_init(char **std_environ)
{
	int	position;
	int	global_size;

	if (!std_environ)
		return (NULL);
	position = 0;
	global_size = get_environ_size(std_environ);
	g_minishell.environ = malloc(sizeof(char *) * (global_size + FOR_NULL));
	if (!g_minishell.environ)
		ft_error_my_exit("malloc() error.\n", 42);
	while (std_environ[position] != NULL)
	{
		g_minishell.environ[position] = ft_strcpy(std_environ[position]);
		if (!g_minishell.environ[position])
		{
			environ_clear_memory_a(g_minishell.environ, position);
			return (NULL);
		}
		position++;
	}
	g_minishell.environ[position] = NULL;
	return (g_minishell.environ);
}

void	environ_clear_memory(char **env)
{
	int	size;
	int	position;

	if (!env)
		return ;
	position = 0;
	size = get_environ_size(env);
	while (position < size)
		free(env[position++]);
	free(env);
}
