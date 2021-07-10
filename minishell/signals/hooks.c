#include "signals.h"

void	ctrl_c_hook(int sgn)
{
	g_minishell.ctrl_c = 1;
	g_minishell.error = "1";
	rl_on_new_line();
	rl_redisplay();
	ft_putstr("  \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sgn;
}

void	ctrl_d_hook(void)
{
	ft_putstr("\033[0;36m\033[1mms: \033[0mexit");
	if (!g_minishell.ctrl_c)
		ft_putstr("\n");
	exit(EXIT_SUCCESS);
}
