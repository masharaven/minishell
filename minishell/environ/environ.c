#include "environ.h"

char	**environ_add_back(char *name, char *value, int clear_name_mem, \
int clear_value_mem)
{
	int	global_size;

	if (!name)
		return (NULL);
	global_size = get_environ_size(g_minishell.environ);
	g_minishell.environ[global_size] = create_var_line(name, value, \
	clear_name_mem, clear_value_mem);
	g_minishell.environ[global_size + FOR_NULL] = NULL;
	return (g_minishell.environ);
}

char	**environ_edit_value(char *name, char *value, int clear_name_mem, \
int clear_value_mem)
{
	int	position;

	if (!name || !g_minishell.environ)
		return (NULL);
	if (!value)
	{
		if (clear_name_mem)
			free(name);
		return (g_minishell.environ);
	}
	position = 0;
	while (g_minishell.environ[position] != NULL)
	{
		if (verify_variable_name(name, g_minishell.environ[position]))
		{
			free(g_minishell.environ[position]);
			g_minishell.environ[position] = create_var_line(name, value, \
			clear_name_mem, clear_value_mem);
			if (g_minishell.environ[position] == NULL)
				return (NULL);
			break ;
		}
		position++;
	}
	return (g_minishell.environ);
}

char	**environ_add(char *name, char *value, int clear_name_mem, \
int clear_value_mem)
{
	if (!name)
		return (NULL);
	if (!verify_variable_exist(name, g_minishell.environ))
	{
		if (environ_new_copy() == NULL)
			return (NULL);
		environ_add_back(name, value, clear_name_mem, clear_value_mem);
	}
	else
	{
		if (environ_edit_value(name, value, clear_name_mem, \
		clear_value_mem) == NULL)
			return (NULL);
	}
	return (g_minishell.environ);
}

char	**environ_remove_line(char *name)
{
	int		pos_new;
	int		pos_old;
	char	**env_new;

	pos_new = 0;
	pos_old = 0;
	env_new = malloc(sizeof(char *) * (get_environ_size(g_minishell.environ) \
	+ FOR_NULL - 1));
	if (!env_new)
		ft_error_my_exit("malloc() error.\n", 42);
	while (g_minishell.environ[pos_old] != NULL)
	{
		if (!verify_variable_name(name, g_minishell.environ[pos_old]))
		{
			if (!environ_copy_line(env_new, pos_new, pos_old))
				return (NULL);
			pos_new++;
		}
		pos_old++;
	}
	env_new[pos_new] = NULL;
	environ_clear_memory(g_minishell.environ);
	g_minishell.environ = env_new;
	return (g_minishell.environ);
}

char	**environ_remove(char *name, int clear_name_mem)
{
	if (!name)
		return (NULL);
	if (!g_minishell.environ)
	{
		verify_clear_name_mem(name, clear_name_mem);
		return (NULL);
	}
	if (!verify_variable_exist(name, g_minishell.environ))
	{
		verify_clear_name_mem(name, clear_name_mem);
		return (g_minishell.environ);
	}
	if (environ_remove_line(name) == NULL)
	{
		verify_clear_name_mem(name, clear_name_mem);
		return (NULL);
	}
	verify_clear_name_mem(name, clear_name_mem);
	return (g_minishell.environ);
}
