#include "binaries.h"

char	*verify_dir(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*valid_path;

	valid_path = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		ent = readdir(dir);
		if (ent == NULL)
			break ;
		if (ent->d_type == DT_REG && ft_strcmp(ent->d_name, name) \
		&& ft_strlen(ent->d_name) == ft_strlen(name))
		{
			valid_path = path;
			break ;
		}
	}
	closedir(dir);
	return (valid_path);
}

void	deallocate_dirs(char **dirs)
{
	int	position;

	if (!dirs)
		return ;
	position = 0;
	while (dirs[position] != NULL)
		free(dirs[position++]);
	free(dirs[position]);
	free(dirs);
}

void	deallocate_name_mem(char *name, int clear_name_mem)
{
	if (name != NULL && clear_name_mem)
		free(name);
}

char	*verify_binary_file(char *name, int clear_name_mem)
{
	int		position;
	char	**dirs;
	char	*path;
	char	*dirs_var;

	path = NULL;
	position = 0;
	dirs_var = get_value_by_name("PATH", g_minishell.environ, 0);
	dirs = ft_split(dirs_var, ':');
	if (!dirs)
		return (NULL);
	while (dirs[position] != NULL)
	{
		if (verify_dir(dirs[position], name) != NULL)
			path = ft_strcpy(dirs[position]);
		if (path != NULL)
			break ;
		position++;
	}
	if (path != NULL)
		path = add_file_name(path, name);
	deallocate_name_mem(name, clear_name_mem);
	deallocate_dirs(dirs);
	free(dirs_var);
	return (path);
}

char	*verify_binary_file_pwd(char *name, int clear_name_mem)
{
	char	*path;
	char	*new_name;

	new_name = cut_file_name(name, clear_name_mem);
	if (!new_name)
		return (NULL);
	path = verify_pwd(new_name);
	if (!path)
	{
		free(new_name);
		return (NULL);
	}
	path = add_file_name(path, new_name);
	free(new_name);
	if (!path)
	{
		free(path);
		return (NULL);
	}
	return (path);
}
