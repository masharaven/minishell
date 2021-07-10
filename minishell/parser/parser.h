#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define TAB '\t'
# define PIPE '|'
# define SPACE ' '
# define EQUAL '='
# define DOLLAR '$'
# define ERR_DEF -1
# define FOR_EQUAL 1
# define FOR_QUOTE 1
# define QUESTION '?'
# define FOR_DOLLAR 1
# define END_OF_LINE 0
# define RELINK_LEFT '<'
# define RELINK_RIGHT '>'
# define QUOTE_SINGLE '\''
# define QUOTE_DOUBLE '\"'
# define FOR_END_OF_LINE 1

typedef enum e_errors
{
	ERROR_MALLOC = 1,
	ERROR_EMPTY_LINE = 2,
	ERROR_NOT_CLOSED_QUOTE = 3
}				t_errors;

typedef enum e_types
{
	TYPE_COMMAND = 1,
	TYPE_RELINK = 2,
	TYPE_ARG = 3
}				t_types;

typedef struct s_token
{
	char	*content;
	int		words;
	int		quotes;
	int		type;
	int		last;
}				t_token;

typedef struct s_minishell
{
	int		ctrl_c;
	char	*error;
	char	**environ;
	int		*fd;
}				t_minishell;

t_minishell	g_minishell;

int		ft_error_my_exit(char *line, int num);

int		get_tokens_size(t_token *tokens);
char	*get_content(t_token *tokens, int id);
int		get_words(t_token *tokens, int id);
int		get_quotes(t_token *tokens, int id);
int		is_last(t_token *tokens, int id);

void	skip_spaces_t(char *line, int *position);
char	*parse_quote_t(char *line, int *position);
char	*parse_word_t(char *line, int *position);
int		get_tokens_count(char *line);
t_token	**initialize_tokens(t_token **tokens, int size);
int		verify_content(t_token *tokens, int token_pos);
void	move_str(int length, char *content, int *position, char *line);
void	skip_spaces(char *line, int *position);
int		get_quote_size(char *line, int *position, int quote);
int		get_word_size(char *line, int *position);
char	*get_variable(char *content, char **variables, int *position, \
int offset);
void	select_value(char *content, char *content_new, \
int *position, char **variables);
char	*get_variable_name(char *content, int *position, int offset);
char	*get_value_by_name(char *name, char **variables, int clear_memory);
char	*replace_variable(char *content, char **variables, int clear_memory);
char	*parse_quote(char *line, int *position, int *words, int *quotes);
char	*parse_word(char *line, int *position, int *words, int *quotes);
char	*parse_blocks(char *line, t_token *tokens);
void	clear_memory(t_token *tokens);
t_token	*tokenize_line(char *line, int *error);

char	*ft_getstrempty(void);
int		ft_isvarchar(int c);
int		ft_strlen(char *str);
char	*ft_strcpy(char *str);
int		ft_strcmp(char *str1, char *str2);
char	*ft_strjoin(char *str1, char *str2, int clear_memory);
char	*ft_straddback(char *str1, char *str2, \
int single_char, int clear_memory);

#endif
