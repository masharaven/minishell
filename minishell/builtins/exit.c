#include "builtins.h"

static int	ft_exit_search_arg(t_token *tokens, t_builtins buil);

// Выход
int	ft_exit(t_token *tokens, t_builtins buil)
{
	int	len;
	int	num;
	int	pos_arg;
	int	rez;

	printf("exit\n");
	len = ft_tokens_len(tokens);
	if (len == 1)
		ft_error_my_exit (NULL, 0);
	buil.pos += 1;
	pos_arg = ft_exit_search_arg(tokens, buil);
	if (pos_arg == 0)
		return (global_error("ms: exit: too many arguments\n", 1, 0, NULL));
	if (pos_arg != -1)
	{
		if (ft_number_my(tokens[pos_arg].content) == 0)
			global_exit(tokens[pos_arg].content, 0);
		rez = ft_atoi_my(tokens[pos_arg].content, &num);
		if (rez == 0)
			global_exit(tokens[pos_arg].content, 0);
		else
			ft_error_my_exit(NULL, num);
	}
	return (1);
}

// Проверяет сколько аргументов получил exit
static int	ft_exit_search_arg(t_token *tokens, t_builtins buil)
{
	int	pos_arg;
	int	num;

	pos_arg = -1;
	while (buil.pos < ft_tokens_len(tokens))
	{
		if (ft_spec_char(tokens[buil.pos].content, tokens[buil.pos].quotes))
			ft_check_special_characters(&buil.pos, tokens[buil.pos].content);
		else
		{
			if (pos_arg == -1)
				pos_arg = buil.pos;
			else
			{
				if (ft_number_my(tokens[pos_arg].content) == 0)
					global_exit(tokens[pos_arg].content, 0);
				if (ft_atoi_my(tokens[pos_arg].content, &num) == 0)
					global_exit(tokens[pos_arg].content, 0);
				else
					return (0);
			}
		}
		buil.pos++;
	}
	return (pos_arg);
}
