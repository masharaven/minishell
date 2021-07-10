#include "builtins.h"

static int	ft_cd_home(void);
static int	ft_cd_search_home(void);
static int	ft_cd_search_arg(t_token *tokens, t_builtins buil);

// Изменяет текущий католог
int	ft_cd(t_token *tokens, t_builtins buil)
{
	int	len;
	int	pos_arg;
	int	rez;

	skipping_redirect(tokens);
	len = ft_tokens_len(tokens);
	buil.pos = buil.pos + 1;
	pos_arg = ft_cd_search_arg(tokens, buil);
	rez = 0;
	if (pos_arg == -1)
		return (ft_cd_home());
	else
	{
		rez = chdir(tokens[pos_arg].content);
		if (rez == -1)
		{
			write (2, "ms: ", 4);
			write (2, tokens[pos_arg].content, \
			ft_strlen(tokens[pos_arg].content));
			return (global_error(": No such file or directory\n", 1, 0, NULL));
		}
	}
	return (global_error(NULL, 0, 1, NULL));
}

// Перемещаемся в домашний католог
static int	ft_cd_home(void)
{
	int		pos_environ;
	char	*name;
	int		rez;

	pos_environ = ft_cd_search_home();
	if (pos_environ != -1)
	{
		if (ft_strlen(g_minishell.environ[pos_environ]) == 5)
			g_minishell.error = "0";
		else
		{
			name = ft_strcpy_start(g_minishell.environ[pos_environ], 5);
			rez = chdir(name);
			free(name);
			if (rez == -1)
				return (global_error_dir(name));
		}
	}
	else
		global_error ("ms: cd: HOME not set\n", 1, 0, NULL);
	return (0);
}

// Ищем домашний католог
static int	ft_cd_search_home(void)
{
	int	len;
	int	i;
	int	pos_environ;

	len = ft_environ_len();
	i = 0;
	pos_environ = -1;
	while (i < len)
	{
		if (ft_strncmp_my(g_minishell.environ[i], "HOME=", 5) == 0)
		{
			pos_environ = i;
			break ;
		}
		i++;
	}
	return (pos_environ);
}

// Ищем аргумент cd
static int	ft_cd_search_arg(t_token *tokens, t_builtins buil)
{
	int	pos_arg;

	pos_arg = -1;
	while (buil.pos < ft_tokens_len(tokens))
	{
		if (ft_spec_char(tokens[buil.pos].content, tokens[buil.pos].quotes))
			ft_check_special_characters(&buil.pos, tokens[buil.pos].content);
		else
		{
			pos_arg = buil.pos;
			break ;
		}
		buil.pos++;
	}
	return (pos_arg);
}
