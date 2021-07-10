#include "binaries.h"

long	get_parts_count(char const *s, char c)
{
	long	pos;
	long	parts;

	pos = 0;
	parts = 0;
	while (*(s + pos))
	{
		while (*(s + pos) == c)
			pos++;
		if (*(s + pos) == 0)
			break ;
		while (*(s + pos) != '\0' && *(s + pos) != c)
			pos++;
		parts++;
	}
	return (parts);
}

long	get_part_length(char const *s, char c)
{
	long	length;

	length = 0;
	while (*(s + length) != '\0' && *(s + length) != c)
		length++;
	return (length);
}

int	create_parts(char ***spltted, char const *s, char c)
{
	long	pos;
	long	part;
	long	pos_part;

	pos = 0;
	part = 0;
	pos_part = 0;
	while (*(s + pos))
	{
		while (*(s + pos) == c)
			pos++;
		if (*(s + pos) == 0)
			break ;
		(*spltted)[part] = malloc(get_part_length(s + pos, c) + 1);
		if ((*spltted)[part] == NULL)
			ft_error_my_exit("malloc() error.\n", 42);
		while (*(s + pos) != '\0' && *(s + pos) != c)
			(*spltted)[part][pos_part++] = *(s + pos++);
		(*spltted)[part][pos_part] = '\0';
		pos_part = 0;
		part++;
	}
	(*spltted)[part] = NULL;
	return (0);
}

void	split_clear_memory(char ***spltted, long parts_created)
{
	long	part;

	part = 0;
	while (part < parts_created)
		free(spltted[part++]);
	free(spltted);
}

char	**ft_split(char const *s, char c)
{
	char	**spltted;
	long	parts_count;
	long	parts_created;

	if (s == NULL)
		return (NULL);
	parts_count = get_parts_count(s, c);
	spltted = malloc((parts_count + 1) * sizeof(char *));
	if (spltted == NULL)
		ft_error_my_exit("malloc() error.\n", 42);
	parts_created = create_parts(&spltted, s, c);
	if (parts_created != 0)
	{
		split_clear_memory(&spltted, parts_created);
		return (NULL);
	}
	return (spltted);
}
