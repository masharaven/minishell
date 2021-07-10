#include "binaries.h"

void	strstr_by_position(char *str_to, char *str_from, int start_position)
{
	int	length;
	int	position;

	length = ft_strlen(str_from);
	position = 0;
	while (start_position < length)
	{
		str_to[position] = str_from[start_position];
		position++;
		start_position++;
	}
	str_to[position] = END_OF_LINE;
}

void	clear_name_memory(char *name, int clear_name_mem)
{
	if (clear_name_mem)
		free(name);
}

char	*cut_file_name(char *name, int clear_name_mem)
{
	int		length;
	char	*name_upd;

	if (name != NULL && (name[0] != '.' || name[1] != '/'))
		return (ft_strcpy(name));
	length = ft_strlen(name);
	if (length <= 2)
	{
		clear_name_memory(name, clear_name_mem);
		return (NULL);
	}
	name_upd = malloc(length - 2 + FOR_END_OF_LINE);
	if (!name_upd)
		ft_error_my_exit("malloc() error.\n", 42);
	strstr_by_position(name_upd, name, 2);
	clear_name_memory(name, clear_name_mem);
	return (name_upd);
}

char	*verify_pwd(char *name)
{
	char	*path;
	char	pwd_path[PATH_MAX];

	if (getcwd(pwd_path, PATH_MAX) == NULL)
		return (NULL);
	path = verify_dir(pwd_path, name);
	if (path != NULL)
		return (ft_strcpy(path));
	return (NULL);
}

char	*add_file_name(char *path, char *name)
{
	char	*path_slash;
	char	*new_path;
	char	*slash;
	char	*name_cpy;

	if (!path || !name)
		return (NULL);
	slash = malloc(2);
	if (!slash)
		ft_error_my_exit("malloc() error.\n", 42);
	slash[0] = '/';
	slash[1] = END_OF_LINE;
	path_slash = ft_strjoin(path, slash, 1);
	name_cpy = ft_strcpy(name);
	if (!path_slash || !name_cpy)
		return (NULL);
	new_path = ft_strjoin(path_slash, name_cpy, 1);
	return (new_path);
}
