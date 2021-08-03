/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutting_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:46:42 by inyang            #+#    #+#             */
/*   Updated: 2021/08/03 23:21:24 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	changed_line_cut(char *line, int *changed, t_all *a)
{
	t_all *b;
	int	strlen;
	int	i;
	int	j;

	b = a;
	i = 0;
	while (b)
	{
		j = 0;
		strlen = px_strlen(b->line_cut);
		b->int_line_cut = malloc(sizeof(int) * strlen);
		while (j < strlen)
		{
			b->int_line_cut[j] = changed[i]; //line <- {(int)line == changed}  
			i++;
			j++;
		}
		i++;
		b = b->next;
	}
}

char	*cutting_int_line(char *line, int **i_int, t_all *a)
{
	int		strlen;
	char	*line_dup;
	t_all 	*b;
	int		i;
	int		j;
	int		k;
	int		env_len;
	int		*changed;
	char	*env_value;
	char	*tmp;
	char	*final;
	
	b = a;
	line_dup = env_to_str(line, i_int);
	strlen = px_strlen(line_dup);
	i = 0;
	j = 0;
	changed = *i_int;
	while (i < strlen)
	{
		if (changed[i] == 3)
			changed[i] = 2;
		if (changed[i] == 4)
			changed[i] = 2;
		if (changed[i] == 8)
		{
			b->next = make_next_page();
			a->pipe_cnt++;
			line_dup[i] = '\0';
			b->line_cut = ft_strdup(&line_dup[j]);
			j = i + 1;
			b = b->next;
		}
		printf("%d", changed[i]);
		i++;
	}
	*i_int = changed;
	if (b)
		b->line_cut = ft_strdup(&line_dup[j]);
	printf("\n\na->line_cut %s\n", a->line_cut);
	if (a->next)
		printf("a->next->line_cut %s\n", a->next->line_cut);
	if (a->next && a->next->next)
		printf("a->next->line_cut %s\n", a->next->next->line_cut);
	printf("\n\na->pipe_cnt %d\n", a->pipe_cnt);
	return (line_dup);
}