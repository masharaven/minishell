#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../builtins/builtins.h"

int		get_next_line(int fd, char **line);
char	*get_cut_gnl(char *str);
char	*get_tail_gnl(char *str);
int		get_check_gnl(char *str);
int		get_end_gnl(char *buffer, int y);

char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	*ft_memmove_gnl(void *dst, const void *src, size_t len);
size_t	ft_strlen_c_gnl(const char *s, char c);

#endif