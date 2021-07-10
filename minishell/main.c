#include "minishell.h"
#include "builtins/builtins.h"

void	shell_init(int args_count, char **args, char **environ)
{
	(void)args_count;
	(void)args;
	g_minishell.ctrl_c = 0;
	g_minishell.error = "0";
	if (environ_init(environ) == NULL)
		exit(EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c_hook);
}

char	*wait_line(void)
{
	char	*line;

	line = readline("\033[0;36m\033[1mms: \033[0m");
	if (line == NULL)
		ctrl_d_hook();
	if (is_line_empty(line, 1))
	{
		g_minishell.error = "1";
		return (NULL);
	}
	return (line);
}

t_token	*get_tokens(char *line)
{
	int		error;
	t_token	*tokens;

	error = 0;
	tokens = tokenize_line(line, &error);
	if (error == ERROR_NOT_CLOSED_QUOTE)
	{
		free(line);
		g_minishell.error = "2";
		printf("ms: syntax error\n");
		return (NULL);
	}
	if (error == ERROR_MALLOC || error == ERROR_EMPTY_LINE)
	{
		printf("ms: error malloc\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}

int	line_handle(t_token *tokens, char *line)
{
	int		tokens_list_size;
	t_token	**tokens_list;

	tokens_list_size = get_tokens_list_size_check(tokens) + 1;
	if (tokens_list_size - 1 == ERR_DEF)
	{
		clear_memory(tokens);
		free(line);
		return (0);
	}
	tokens_list = check_pipe(tokens);
	if (tokens_list_size == 1)
		check_command(tokens);
	else
		evaluate_tokens(tokens_list, tokens_list_size);
	check_pipe_free(tokens_list, tokens_list_size);
	return (1);
}

int	main(int args_count, char **args, char **environ)
{
	char	*line;
	t_token	*tokens;

	shell_init(args_count, args, environ);
	shlvl_growing();
	while (1)
	{
		g_minishell.fd = NULL;
		line = wait_line();
		if (line == NULL)
			continue ;
		add_history(line);
		tokens = get_tokens(line);
		if (tokens == NULL)
			continue ;
		if (!line_handle(tokens, line))
			continue ;
		clear_memory(tokens);
		free(line);
	}
	environ_clear_memory(g_minishell.environ);
	exit(EXIT_SUCCESS);
}
