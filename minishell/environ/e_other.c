#include "environ.h"

int	verify_variable_exist(char *name, char **env)
{
	int	position;
	int	line_len;
	int	name_len;

	if (!name || !env)
		return (0);
	position = 0;
	name_len = ft_strlen(name);
	while (env[position] != NULL)
	{
		line_len = ft_strlen(env[position]);
		if (line_len >= name_len && ft_strcmp(name, env[position]) \
		&& (env[position][name_len] == EQUAL || env[position][name_len] == \
		END_OF_LINE))
			return (1);
		position++;
	}
	return (0);
}

int	verify_variable_name(char *name, char *line)
{
	int	name_len;
	int	line_len;

	if (!name || !line)
		return (0);
	name_len = ft_strlen(name);
	line_len = ft_strlen(line);
	if (line_len >= name_len && ft_strcmp(name, line) \
		&& (line[name_len] == EQUAL || line[name_len] == END_OF_LINE))
		return (1);
	return (0);
}

char	**environ_new_copy(void)
{
	int		position;
	int		global_size;
	char	**env_new;

	if (!g_minishell.environ)
		return (NULL);
	position = 0;
	global_size = get_environ_size(g_minishell.environ);
	env_new = malloc(sizeof(char *) * (global_size + FOR_NULL + 1));
	if (!env_new)
		ft_error_my_exit("malloc() error.\n", 42);
	while (g_minishell.environ[position] != NULL)
	{
		env_new[position] = ft_strcpy(g_minishell.environ[position]);
		if (!env_new[position])
		{
			environ_clear_memory_a(env_new, position);
			return (NULL);
		}
		position++;
	}
	env_new[position] = NULL;
	environ_clear_memory(g_minishell.environ);
	g_minishell.environ = env_new;
	return (g_minishell.environ);
}

char	*create_var_line(char *name, char *value, int clear_name_mem, \
int clear_value_mem)
{
	char	*first_part;
	char	*line;

	if (!name || !g_minishell.environ)
		return (NULL);
	if (!value)
	{
		line = ft_strcpy(name);
		if (clear_name_mem)
			free(name);
		return (line);
	}
	first_part = ft_strjoin(name, "=", 0);
	if (clear_name_mem)
		free(name);
	if (!first_part)
		return (NULL);
	line = ft_strjoin(first_part, value, 0);
	free(first_part);
	if (clear_value_mem)
		free(value);
	return (line);
}

void	verify_clear_name_mem(char *name, int clean_name_mem)
{
	if (name != NULL && clean_name_mem)
		free(name);
}
