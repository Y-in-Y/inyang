#include "parsing.h"

char	*ft_itoa(int n)
{
	long long	num;
	char		str[20];
	int			idx;
	char		*result;

	idx = 0;
    if (n == 0)
        return (ft_strdup("0"));
	num = (long long)n;
	if (num < 0)
		num = -num;
	while (num > 0)
	{
		str[idx++] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		str[idx++] = '-';
	str[idx] = '\0';
	result = (char *)malloc(sizeof(char) * (px_strlen(str) + 1));
    if (!result)
		return (0);
	result[px_strlen(str)] = '\0';
    while (--idx >= 0)
		result[px_strlen(str) - 1 - idx] = str[idx];
	return (result);
}