#include "parser.h"

void	skip_spaces_t(char *line, int *position)
{
	while ((line[*position] == SPACE || line[*position] == TAB) \
	&& line[*position] != END_OF_LINE)
		(*position)++;
}
