#include "redirects.h"

void	clear_text_memory(char *text, int clear_text_mem)
{
	if (clear_text_mem && text != NULL)
		free(text);
}

char	*create_tmp_file(char *text, int clear_text_mem)
{
	int	fd;
	int	length;

	if (!text)
	{
		clear_text_memory(text, clear_text_mem);
		return (NULL);
	}
	fd = open(TMP_FILE_PATH, O_CREAT | O_WRONLY);
	if (fd == -1)
	{
		clear_text_memory(text, clear_text_mem);
		close(fd);
		return (NULL);
	}
	length = ft_strlen(text);
	if (write(fd, text, length) == -1)
	{
		clear_text_memory(text, clear_text_mem);
		close(fd);
		return (NULL);
	}
	return (TMP_FILE_PATH);
}
