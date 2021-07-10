#include "environ.h"

void	shlvl_growing(void)
{
	char	*value;
	char	*value_upd;

	value = get_value_by_name("SHLVL", g_minishell.environ, 0);
	if (value == NULL)
	{
		environ_add("SHLVL", "1", 0, 0);
		return ;
	}
	value_upd = ft_itoa(ft_atoi(value) + 1);
	free(value);
	environ_add("SHLVL", value_upd, 0, 1);
}
