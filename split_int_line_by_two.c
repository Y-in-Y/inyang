/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_int_by_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:05:59 by inyang            #+#    #+#             */
/*   Updated: 2021/07/24 16:06:28 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	ft_cnt(int *s, int c, int strlen)
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

static int		ft_n_malloc(char **all, size_t k, size_t cnt)
{
	if (!(all[k] = malloc(sizeof(char) * (cnt + 1))))
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

static size_t	ft_index(size_t i, int *s, int c, int strlen)
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

static int		ft_fill(int *int_line, char const *s, int c, char **all, int strlen)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	cnt;

	i = 0;
	k = 0;
	/* 무슨 문장 들어왔나 체크용 */
	printf("command line : %s\n",s);
	/* 여기까지 */
	while ((int)i < strlen)
	{
		while ((int)i < strlen && int_line[i] == c)
			i++;
		if (i >= strlen)
			break ;
		cnt = ft_index(i, int_line, c, strlen);
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

char			**split_args(int *int_line, char *s, int c)
{
	size_t	len;
	char	**all;
	int		strlen;

	if (!s)
		return (NULL);
	strlen = px_strlen(s);
	len = ft_cnt(int_line, c, strlen);
	if (!(all = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	int check;
	if ((check = ft_fill(int_line, s, c, all, strlen)) != 0)
		return (NULL);
	all[len] = NULL;
	return (all);
}
