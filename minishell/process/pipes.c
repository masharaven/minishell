#include "process.h"
#include "../builtins/builtins.h"

void	close_descriptors(t_descriptors *descriptors, int count)
{
	int	position;

	position = 0;
	while (position < count)
	{
		close(descriptors[position].descriptor[0]);
		close(descriptors[position].descriptor[1]);
		position++;
	}
}

t_descriptors	*create_descriptions(int count)
{
	int				position;
	t_descriptors	*descriptors;

	descriptors = malloc(sizeof(t_descriptors) * count);
	if (!descriptors)
		ft_error_my_exit("malloc() error.\n", 42);
	position = 0;
	while (position < count)
	{
		if (pipe(descriptors[position].descriptor) < 0)
		{
			close_descriptors(descriptors, position);
			ft_error_my_exit("pipe() error.\n", 42);
		}
		position++;
	}
	return (descriptors);
}

int	is_redirect_exist(t_token *tokens)
{
	int	length;
	int	position;

	length = ft_tokens_len(tokens);
	position = 0;
	while (position < length)
	{
		if (ft_strcmp(tokens[position].content, "<<") \
		&& tokens[position].quotes == 0 \
		&& ft_strlen(tokens[position].content) == ft_strlen("<<"))
			return (1);
		position++;
	}
	return (0);
}

void	parent_body(t_token **tokens_list, t_descriptors *descriptors, \
int count, int position)
{
	g_minishell.fd = NULL;
	if (!is_redirect_exist(tokens_list[position]))
		dup2(descriptors[position].descriptor[0], STDIN_FILENO);
	if (!is_redirect_exist(tokens_list[position]) && position < count - 1)
		dup2(descriptors[position + 1].descriptor[1], STDOUT_FILENO);
	if (is_redirect_exist(tokens_list[position]) && position < count - 1)
		g_minishell.fd = &(descriptors[position + 1].descriptor[1]);
	if (!is_redirect_exist(tokens_list[position]))
	{
		close_descriptors(descriptors, count);
		free(descriptors);
	}
	check_command(tokens_list[position]);
	close(*g_minishell.fd);
	if (is_redirect_exist(tokens_list[position]))
	{
		close_descriptors(descriptors, count);
		free(descriptors);
	}
	exit(EXIT_SUCCESS);
}

void	evaluate_tokens(t_token **tokens_list, int count)
{
	pid_t			pid;
	int				position;
	t_descriptors	*descriptors;

	descriptors = create_descriptions(count);
	position = 0;
	while (position < count)
	{
		pid = fork();
		if (pid < 0)
			ft_error_my_exit("fork() error.\n", 42);
		if (pid == 0)
			parent_body(tokens_list, descriptors, count, position);
		close_descriptors(descriptors, ++position);
		pid = wait(NULL);
	}
	close_descriptors(descriptors, count);
	free(descriptors);
}
