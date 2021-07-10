#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buffer;
	int			y;
	int			buffer_size_gnl;

	buffer_size_gnl = 42;
	y = 42;
	if (fd < 0 || !line || buffer_size_gnl <= 0)
		return (-1);
	buffer = malloc(sizeof(char) * (buffer_size_gnl + 1));
	if (!buffer)
		ft_error_my_exit("malloc error", 0);
	while (y)
	{
		if (get_check_gnl(str))
			break ;
		y = read(fd, buffer, buffer_size_gnl);
		if (y == -1)
			return (get_end_gnl(buffer, y));
		buffer[y] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	*line = get_cut_gnl(str);
	str = get_tail_gnl(str);
	return (get_end_gnl(buffer, y));
}

char	*get_cut_gnl(char *str)
{
	char	*str_new;
	int		i;

	if (!str)
		return (NULL);
	str_new = malloc(sizeof(char) * (ft_strlen_c_gnl(str, '\n') + 1));
	if (!str_new)
		ft_error_my_exit("malloc error", 0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		str_new[i] = str[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}

char	*get_tail_gnl(char *str)
{
	char	*str_new;
	int		size;
	int		i;

	if (!str)
		return (NULL);
	size = ft_strlen_c_gnl(str, '\n');
	if (str[size] == '\0')
	{
		free(str);
		return (NULL);
	}
	str_new = malloc(sizeof(char) * (ft_strlen_c_gnl(str, '\0') - size + 1));
	if (!str_new)
		ft_error_my_exit("malloc error", 0);
	size++;
	i = 0;
	while (str[size + i])
	{
		str_new[i] = str[size + i];
		i++;
	}
	str_new[i] = '\0';
	free(str);
	return (str_new);
}

int	get_check_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_end_gnl(char *buffer, int y)
{
	free(buffer);
	if (y == -1)
		return (y);
	else if (y == 0)
		return (y);
	else
		return (1);
}
