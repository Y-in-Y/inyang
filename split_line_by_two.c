/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line_by_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:05:59 by inyang            #+#    #+#             */
/*   Updated: 2021/08/10 00:35:32 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_cnt(int *s, int c, int strlen)
{
	size_t	cnt;
	int		*tmp;
	int		i;

	cnt = 0;
	tmp = s;
	i = 0;
	while (i < strlen)
	{
		if (tmp[i] == c)
			i++;
		else
		{
			while (i < strlen && tmp[i] != c)
				i++;
			cnt++;
		}
	}
	return (cnt);
}

int	ft_n_malloc(char **all, size_t k, size_t cnt)
{
	all[k] = malloc(sizeof(char) * (cnt + 1));
	if (!(all[k]))
	{
		while (k > 0)
		{
			k--;
			free(all[k]);
		}
		free(all);
		return (1);
	}
	return (0);
}

size_t	ft_index(size_t i, int *s, int c, int strlen)
{
	size_t	cnt;

	cnt = 0;
	while ((int)i < strlen && s[i] != c)
	{
		i++;
		cnt++;
	}
	return (cnt);
}

int	ft_fill(int *int_line, char const *s, int c, char **all)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	cnt;

	i = 0;
	k = 0;
	while ((int)i < px_strlen((char *)s))
	{
		while ((int)i < px_strlen((char *)s) && int_line[i] == c)
			i++;
		if (i >= (size_t)px_strlen((char *)s))
			break ;
		cnt = ft_index(i, int_line, c, px_strlen((char *)s));
		i += cnt;
		if (ft_n_malloc(all, k, cnt))
			return (1);
		l = 0;
		j = i - cnt;
		while (j < i)
			all[k][l++] = (char)s[j++];
		all[k++][l] = '\0';
	}
	return (0);
}

char	**split_args(int *int_line, char *s, int c)
{
	size_t	len;
	char	**all;
	int		strlen;

	if (!s)
		return (NULL);
	strlen = px_strlen(s);
	len = ft_cnt(int_line, c, strlen);
	all = malloc(sizeof(char *) * (len + 1));
	if (!(all))
		return (NULL);
	if (ft_fill(int_line, s, c, all) != 0)
		return (NULL);
	all[len] = NULL;
	return (all);
}
