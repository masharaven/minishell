#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <dirent.h>
# include <stdlib.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/syslimits.h>

# include "other/other.h"
# include "parser/parser.h"
# include "process/process.h"
# include "environ/environ.h"
# include "signals/signals.h"
# include "binaries/binaries.h"
# include "redirects/redirects.h"

//Readline library:
char	*readline(const char *prompt);
int		add_history(const char *string_for_history);
int		rl_on_new_line(void);
void	rl_redisplay(void);
void	rl_replace_line(const char *buffer, int something);

#endif
