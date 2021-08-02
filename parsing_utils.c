/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:58 by inyang            #+#    #+#             */
/*   Updated: 2021/08/03 01:49:44 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char		*ft_strdup(char *src)
{
	char	*result;
	int		i;

	i = 0;
	while (src[i])
		i++;
	result = (char *)malloc(sizeof(char) * i + 1);
	if (result == 0)
		return (0);
	i = 0;
	while (src[i])
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int		px_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*px_strjoin(char *s1, char *s2)
{
	int		i;
	char	*buf;

	if (!(buf = malloc(sizeof(char) * (px_strlen(s1) + px_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*s1)
		buf[i++] = *s1++;
	while (*s2)
		buf[i++] = *s2++;
	buf[i] = '\0';
	return (buf);
}

