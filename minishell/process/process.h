#ifndef PROCESS_H
# define PROCESS_H

# include "../minishell.h"
# include "../parser/parser.h"
# include "../builtins/builtins.h"

typedef struct s_descriptors
{
	int	descriptor[2];
}				t_descriptors;

typedef struct s_relink_info
{
	char	*relink_path;
	int		write_mode;
}				t_relink_info;

void	evaluate_tokens(t_token **tokens_list, int count);
int		move_descriptors(char *relink_path, int write_mode, int *stdout_fd);
int		move_descriptors_back(int stdout_fd);
int		process_run(char *path, char **args, char *relink_path, int write_mode);
int		process_run_smart(char *path, char **args, t_relink_info relinkInfo, \
char *text);

#endif