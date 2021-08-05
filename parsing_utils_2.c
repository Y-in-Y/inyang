/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 23:13:23 by inyang            #+#    #+#             */
/*   Updated: 2021/08/04 16:17:59 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

long long	make_num_plus(int n)
{
	int	num;

	num = (long long)n;
	if (num < 0)
		num = -num;
	return (num);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		str[20];
	int			idx;
	char		*result;

	idx = 0;
	if (n == 0)
		return (ft_strdup("0"));
	num = make_num_plus(n);
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

int	px_strcmp(char *dst, char *src)
{
	int		i;

	if (!dst || !src)
		return (-1);
	i = 0;
	while (dst[i])
	{
		if (dst[i] == src[i])
			i++;
		else
			return (0);
	}
	if (src[i] != '\0')
		return (0);
	return (1);
}

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
