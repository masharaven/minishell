#include "builtins.h"

// printf("line =%s | ret =%d\n", line, ret);
// printf("%s\n", data);
char	*relink_read_file(char *name_file)
{
	char	*line;
	char	*data;
	int		fd;
	int		ret;

	data = NULL;
	line = NULL;
	data = malloc(sizeof(char) * 1);
	if (data == NULL)
		ft_error_my_exit("malloc error", 0);
	data[0] = '\0';
	fd = open (name_file, O_RDONLY);
	ret = 42;
	while (ret)
	{
		if (ret == 1)
			data = ft_strjoin_my(data, "\n", 0);
		ret = get_next_line(fd, &line);
		data = ft_strjoin_my(data, line, 0);
		if (data == NULL)
			ft_error_my_exit("malloc error", 0);
		free(line);
	}
	close (fd);
	return (data);
}
