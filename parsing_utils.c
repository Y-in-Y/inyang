/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:58 by inyang            #+#    #+#             */
/*   Updated: 2021/07/08 16:17:39 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char		*ft_strdup(const char *src)
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
		if (changed[i] == 8)
			i += 1;
		if (changed[i] == 2)
			i += 1;
		while (j < strlen)
		{
			b->int_line_cut[j] = changed[i];
			i++;
			j++;
		}
		printf(">>>>>>line in page %s\n>>>>>>int line in page ", b->line_cut);
		int k = 0;
		while (k < strlen)
			printf("%d", b->int_line_cut[k++]);
		printf("\n");
		i++;
		b = b->next;
	}
}

t_all	*make_next_page(void)
{
	t_all *a;

	a = (t_all *)malloc(sizeof(t_all));
	a->redir_list = (t_list *)malloc(sizeof(t_list));
	a->next = NULL;
	a->redir_list->next = NULL;
	a->redir_list->redir_flag = 0;
	a->redir_list->file = NULL;
	return (a);
}

void	cutting_int_line(char *line, int *changed, t_all *a)
{
	int		strlen;
	char	*line_dup;
	t_all 	*b;
	
	b = a;
	line_dup = ft_strdup(line);
	strlen = px_strlen(line);
	printf("%s\n", line);
	printf("dup %s\n", line_dup);
	printf("%d\n", strlen);
	int i = 0;
	while (i < strlen)
		printf("%d", changed[i++]);
	printf("\n");
	i = 0;
	int j = 0;
	while (i < strlen)
	{
		if (changed[i] == 8)
		{
			b->next = make_next_page();
			a->pipe_cnt++;
			line_dup[i] = '\0';
			b->line_cut = ft_strdup(&line_dup[j]);
			j = i + 2;
			b = b->next;
		}
		printf("%d", changed[i]);
		i++;
	}
	if (b)
		b->line_cut = ft_strdup(&line_dup[j]);
	printf("\n\na->line_cut %s\n", a->line_cut);
	if (a->next)
		printf("a->next->line_cut %s\n", a->next->line_cut);
	if (a->next && a->next->next)
		printf("a->next->line_cut %s\n", a->next->next->line_cut);
	printf("\n\na->pipe_cnt %d\n", a->pipe_cnt);
	free(line_dup);
}

int		px_strlen(char *s)
{
	int i;

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

int		px_gnl(char **line)
{
	int		size;
	char	buf[2];
	char	*store;
	char	*temp;

	size = 1;
	store = px_strjoin("", "");
	buf[size] = '\0';
	while (size && buf[0] != '\n')
	{
		size = read(0, buf, 1);
		if (size <= 0)
			return (0);
		if (buf[0] != '\n' && size != 0)
		{
			temp = px_strjoin(store, buf);
			free(store);
			store = temp;
		}
	}
	*line = store;
	return (size);
}
