#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"
# include "../builtins/builtins.h"

void	ctrl_d_hook(void);
void	ctrl_c_hook(int sgn);

#endif
