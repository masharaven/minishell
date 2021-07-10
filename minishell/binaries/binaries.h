#ifndef BINARIES_H
# define BINARIES_H

# include "../minishell.h"
# include "../builtins/builtins.h"

char	**ft_split(char const *s, char c);
char	*verify_dir(char *path, char *name);
char	*cut_file_name(char *name, int clear_name_mem);
char	*verify_pwd(char *name);
char	*add_file_name(char *path, char *name);
char	*get_value_by_name(char *name, char **variables, int clear_memory);

char	*verify_binary_file(char *name, int clear_name_mem);
char	*verify_binary_file_pwd(char *name, int clear_name_mem);

#endif
