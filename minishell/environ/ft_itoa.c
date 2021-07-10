#include "environ.h"

static char	num_to_char(int a)
{
	return (a + '0');
}

static int	bytes_of_int(int n)
{
	long	count_bytes;

	if (n == 0)
		return (1);
	count_bytes = 0;
	if (n < 0)
		count_bytes++;
	while (n != 0)
	{
		n /= 10;
		count_bytes++;
	}
	return (count_bytes);
}

static void	write_to_str(char *str, int n, int bytes, int wave)
{
	if (n < 10)
		*(str + bytes - wave - 1) = num_to_char(n);
	else
	{
		write_to_str(str, n / 10, bytes, wave + 1);
		*(str + bytes - wave - 1) = num_to_char(n % 10);
	}
}

static void	write_to_addr(char *addr, char *str)
{
	long	pos;
	long	str_len;

	pos = 0;
	str_len = ft_strlen(str);
	while (pos < str_len)
	{
		*(addr + pos) = *(str + pos);
		pos++;
	}
	*(addr + pos) = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		bytes;

	bytes = bytes_of_int(n);
	str = malloc(bytes + 1);
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		write_to_addr(str, "-2147483648");
	else if (n == 0)
		write_to_addr(str, "0");
	else if (n > 0)
		write_to_str(str, n, bytes, 0);
	else
	{
		write_to_str(str, -n, bytes, 0);
		*str = '-';
	}
	*(str + bytes) = '\0';
	return (str);
}
