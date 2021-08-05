/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutting_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:46:42 by inyang            #+#    #+#             */
/*   Updated: 2021/08/06 01:13:18 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	changed_line_cut(char *line, int *changed, t_all *a)
{
	t_all	*b;
	int		strlen;
	int		i;
	int		j;

	b = a;
	i = 0;
	while (b)
	{
		j = 0;
		strlen = px_strlen(b->line_cut);
		b->int_line_cut = malloc(sizeof(int) * strlen);
		while (j < strlen)
		{
			b->int_line_cut[j] = changed[i];
			i++;
			j++;
		}
		i++;
		b = b->next;
	}
}

int	split_by_pipe(t_all *b, t_all *a, int *idx, char *line_dup)
{
	int	i;
	int	j;

	i = idx[0];
	j = idx[1];
	b->next = make_next_page();
	line_dup[i] = '\0';
	b->line_cut = ft_strdup(&line_dup[j]);
	a->pipe_cnt++;
	j = i + 1;
	return (j);
}

int	init_int_val(char *line_dup, int *idx)
{
	int	strlen;

	strlen = px_strlen(line_dup);
	*idx = 0;
	*(idx + 1) = 0;
	return (strlen);
}

char	*cutting_int_line(char *line, int **i_int, t_all *a)
{
	char	*line_dup;
	t_all	*b;
	int		idx[2];
	int		strlen;
	int		*changed;

	b = a;
	line_dup = env_to_str(line, i_int);
	strlen = init_int_val(line_dup, idx);
	changed = *i_int;
	while (idx[0] < strlen)
	{
		if (changed[idx[0]] == 3 || changed[idx[0]] == 4)
			changed[idx[0]] = 2;
		if (changed[idx[0]] == 8)
		{
			idx[1] = split_by_pipe(b, a, idx, line_dup);
			b = b->next;
		}
		(idx[0])++;
	}
	*i_int = changed;
	if (b)
		b->line_cut = ft_strdup(&line_dup[idx[1]]);
	// printf("\n\na->line_cut %s\n", a->line_cut);
	// if (a->next)
	// 	printf("a->next->line_cut %s\n", a->next->line_cut);
	// if (a->next && a->next->next)
	// 	printf("a->next->line_cut %s\n", a->next->next->line_cut);
	// printf("\n\na->pipe_cnt %d\n", a->pipe_cnt);
	return (line_dup);
}
