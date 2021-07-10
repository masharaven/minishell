#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "../minishell.h"
# include "../builtins/builtins.h"

# define TMP_FILE_PATH "/tmp/minishell"

char	*create_tmp_file(char *text, int clear_text_mem);
char	*relink_read_text(char *stop_str, int clear_stopstr_mem);

#endif
