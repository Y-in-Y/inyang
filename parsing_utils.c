/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:33:58 by inyang            #+#    #+#             */
/*   Updated: 2021/07/30 05:04:56 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		// int x = -1;
		// while (++x < strlen)
		// 	printf("%d", changed[x]);
		b->int_line_cut = malloc(sizeof(int) * strlen);
		// if (changed[i] == 8)
		// 	i += 1;
		// if (changed[i] == 2)
		// 	i += 1;
		while (j < strlen)
		{
			b->int_line_cut[j] = changed[i]; //line <- {(int)line == changed}  
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

char	*env_to_str(char *line, int **changed)
{
	int		i;
	int		j;
	int		idx;
	int		env_end_idx;
	int		*tmp;
	int		*new_int;
	char	*new_line;
	char	*tmp_s;
	char	*env_value;
	int		env_len;

	new_line = ft_strdup(line);
	i = 0;
	while (new_line && new_line[i])
	{
		tmp = *changed;
		if (tmp[i] != 5)
			i++;
		else if (tmp[i] == 5) //love.......
		{
			if (new_line[i] == '$' && new_line[i + 1] == '?')
				tmp[i + 1] = 5;
			j = i;
			while (tmp[j] == 5)
				j++;
			env_value = find_env_value(&new_line[i + 1]);
			printf("env value is %s\n", env_value);
			env_len = px_strlen(env_value);
			printf("env value is %s\n", env_value);
			if (env_value)
			{
				new_line[i] = '\0';
				tmp_s = px_strjoin(new_line, env_value); //newline[0] ~ newline[i - 1] + env_value
				free(new_line);
				new_line = px_strjoin(tmp_s, &(line[j])); // newline[0] ~ newline[i - 1] + env_value + newline[j] ~ end // newline[i] ~ newline[j - 1] 를 env_value 로 교체
				free(tmp_s);
				new_int = (int *)malloc(sizeof(int) * px_strlen(new_line));
				idx = 0;
				while (idx < i) // env 이전 int
				{
					new_int[idx] = tmp[idx];
					idx++;
				}
				while (idx < i + env_len) // env 가 있는 부분
				{
					new_int[idx] = 1;
					idx++;
				}
				i = idx;
				while (idx < px_strlen(new_line)) // env 끝난부분
				{
					new_int[idx] = tmp[j];
					j++;
					idx++;
				}
				free(tmp);
				*changed = new_int;
			}
			else // value 못찾으면 $있어도 단순출력처립ㅂ
			{
				while (tmp[i] == 5)
				{
					tmp[i] = 1;
					i++; //hi >< 힛
				}
			}
		}
	}
	return (new_line);
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
	printf("sorega new line~~~~~ \n%s\n", line_dup);
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
