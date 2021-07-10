#ifndef ENVIRON_H
# define ENVIRON_H

# include "../minishell.h"
# include "../builtins/builtins.h"

# define FOR_NULL 1

char	*ft_itoa(int n);
int		ft_atoi(char *str);
void	shlvl_growing(void);

char	**environ_init(char **std_environ);
char	**environ_add(char *name, char *value, int clear_name_mem, \
int clear_value_mem);
char	**environ_remove(char *name, int clear_name_mem);

void	environ_clear_memory_a(char **env, int size);
void	environ_clear_memory(char **env);
int		get_environ_size(char **env);
int		environ_copy_line(char **env_new, int pos_new, int pos_old);

char	**environ_new_copy(void);
int		verify_variable_name(char *name, char *line);
int		verify_variable_exist(char *name, char **env);
char	*create_var_line(char *name, char *value, int clear_name_mem, \
int clear_value_mem);
void	verify_clear_name_mem(char *name, int clean_name_mem);

#endif
