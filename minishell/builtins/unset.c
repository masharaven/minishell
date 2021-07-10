#include "builtins.h"

// Удаляет переменную
int	ft_unset(t_token *tokens, t_builtins buil)
{
	int	log_err;
	int	temp;

	skipping_redirect(tokens);
	log_err = 0;
	buil.pos += 1;
	while (buil.pos < ft_tokens_len(tokens))
	{
		if (ft_spec_char(tokens[buil.pos].content, tokens[buil.pos].quotes))
			ft_check_special_characters(&buil.pos, tokens[buil.pos].content);
		else
		{
			if (ft_isvarchar_line(tokens[buil.pos].content) == 1)
				environ_remove(tokens[buil.pos].content, 0);
			else
			{
				temp = global_error_r("unset", tokens[buil.pos].content, 1, 1);
				if (temp == 1)
					log_err = 1;
			}
		}
		buil.pos++;
	}
	return (global_error(NULL, log_err, 1, NULL));
}
