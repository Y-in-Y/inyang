#include "parsing.h"

int	ft_strncmp(char *dst, char *src, int size)
{
	int		i;

	if (!dst || !src || size < 1)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (dst[i] == src[i])
			i++;
		else
			return (0);
	}
	return (1);
}