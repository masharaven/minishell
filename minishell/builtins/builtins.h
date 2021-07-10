#ifndef BUILTINS_H
# define BUILTINS_H

# include <string.h>
# include "../minishell.h"
# include "../parser/parser.h"
# include "../gnl_m/get_next_line.h"
# include <fcntl.h>

# define SYNTAX_ERROR "ms: syntax error near unexpected token"
// Для правильного вывода данных
typedef struct s_builtins
{
	int		file_pos;
	int		recording_mode;
	int		pos;
}				t_builtins;

// tokens_part.c (5)
int		ft_tokens_count(t_token *tokens, int start);
int		get_tokens_list_size(t_token *tokens);
int		get_tokens_list_size_check (t_token *tokens);
void	check_pipe_p(t_token *tokens, t_token **tokens_list, int start, int i);
t_token	**check_pipe(t_token *tokens);

//global error.c (5)
int		global_error(char *line, int err, int ret, char *token);
int		global_error_r(char *line, char *token, int err, int ret);
void	global_exit(char *token, int code);
void	skipping_redirect(t_token *tokens);
char	*redirect_data(t_token *tokens);

// utilits_1.c (5)
int		ft_number_my(char *str);
int		ft_atoi_my(const char *str, int *value);
char	*ft_strjoin_my(char *s1, char *s2, int space);
int		ft_strncmp(char *s1, char *s2);
char	*ft_strdup(char *s1);

// utilits_2.c (5)
int		ft_isvarchar_line(char *line);
int		ft_environ_len(void);
int		is_exist(char *path);
int		ft_export_name_len(char *line);
int		ft_export_value_len(char *line, int len_name);

// utilits_3.c (5)
void	ft_srtcopy_my(char *orig, char *copy, int len);
void	ft_srtcopy_start_my(char *orig, char *copy, int start);
int		ft_strncmp_my(char *s1, char *s2, int n);
char	*ft_strcpy_start(char *str, int start);
int		is_f_ex(char *path);

// utilits_4.c (5)
void	check_pipe_free(t_token	**tokens_list, int count_tok);
int		global_error_dir(char *line);
int		global_error_com(char *line);
int		size_body(t_token *tokens, int i, int *count_pipe);
int		ft_check_special_characters_mode(int *pos, char *line);

// utilits_5.c (5)
char	*relink_read_file(char *name_file);

// utilits_minishell.c (5)
int		ft_tokens_len(t_token *tokens);
int		ft_spec_char(char *line, int quotes);
int		ft_error_my(char *line);
int		ft_error_my_exit(char *line, int num);
int		ft_check_special_characters(int *pos, char *line);

// utilits_minishell_2.c (5)
char	**ft_pas_arg_program(t_token *tokens, char **argc_pass);
void	ft_free_my(char **tab);
int		ft_cmp_n(char *str1, char *str2, int n);

// special_characters.c (5)
int		creat_file_redirect_out(t_token *tokens, int *file_pos, int pos);
int		creat_file_redirect_out_mode(t_token *tokens, int *file_pos, int pos);
int		creat_file_redirect_inp(t_token *tokens, int pos);
int		creat_file_redirect_inp_mode(t_token *tokens, int pos);
int		ft_pipe(t_token *tokens, int pos);

// start_program.c (5)
int		ft_start_program(t_token *tokens, t_builtins buil);
int		ft_start_command(t_token *tokens, t_builtins buil);

// main_builtins.c (5)
int		check_command(t_token *tokens);

// utilits_sorting.c (5)
void	ft_tokens_sort(int fd);

// cd.c (4)
int		ft_cd(t_token *tokens, t_builtins buil);
// echo.c (4)
int		ft_echo(t_token *tokens, t_builtins buil);
// env.c  (2)
int		ft_env(t_token *tokens, t_builtins buil);
// exit.c ()
int		ft_exit(t_token *tokens, t_builtins buil);
// export.c (4)
int		ft_export(t_token *tokens, t_builtins buil);
// pwd.c (1)
int		ft_pwd(t_token *tokens, t_builtins buil);
// unset.c (1)
int		ft_unset(t_token *tokens, t_builtins buil);

#endif
