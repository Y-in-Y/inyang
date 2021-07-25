/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:17:22 by inyang            #+#    #+#             */
/*   Updated: 2021/07/26 03:33:32 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		s_len;
	char		*str;

	if (s == 0)
		return (0);
	s_len =	px_strlen(s);
	if (start > s_len)
	{
		if (!(str = (char *)malloc(sizeof(char) * 1)))
			return (0);
		str[0] = '\0';
		return (str);
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	is_there_quote(t_all *a)
{
	int		i;
	t_all	*b;
	char	*tmp;
	int		*tmp_int;
	int		strlen;

	b = a;
	i = 0;
	while (b->arg[i])
	{
		strlen = px_strlen(b->arg[i]);
		tmp_int = malloc(sizeof(int) * strlen);
		line_to_changed(b->arg[i], tmp_int, b); //스플릿 다시 하려다 눈 빠질 것 같아서 잘린 arg를 다시 파싱했습니다
		if (tmp_int[0] != 3 && tmp_int[0] != 4)
		{
			printf("quote deleted b->arg[%d] = %s\n", i, b->arg[i]);
			i++;
		}
		else
		{
			tmp = ft_substr(b->arg[i], 1, strlen - 2);
			free(b->arg[i]);
			b->arg[i] = tmp;
			printf("quote deleted b->arg[%d] = %s\n", i, (b->arg[i]));
			i++;
		}
	}
}

// void		is_there_env(t_all *a)
// {
// 	int		i;
// 	t_all	*b;

// 	b = a;
// 	i = -1;
// 	while (b->arg[++i])
// 	{
// 		if ((b->arg[i][0] == '$')
// 		{
			
// }

char		*change_arg(char *s1, char *s2)
{
	int		i;
	char	*buf;
	
	buf = malloc(sizeof(char) * (px_strlen(s2) + 1));
	printf("char s2 %s\n", s2);
	i = 0;
	while (s2[i])
	{
		buf[i] = s2[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
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

void		is_cmd_echo(t_all *a)
{
	t_all	*b;
	int		echo_here;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	b = a;
	if (b->cmd == NULL)
		return ;
	tmp = b->arg[1];
	b->echo_n_cnt = 0;
	i = -1;
	while (b->arg[++i])
	{
		if ((b->arg[i][0] == 'e' || b->arg[i][0] == 'E')
			&& (b->arg[i][1] == 'c' || b->arg[i][1] == 'C')
			&& (b->arg[i][2] == 'h' || b->arg[i][2] == 'H')
			&& (b->arg[i][3] == 'o' || b->arg[i][3] == 'O'))
		{
			if (px_strcmp(b->cmd, "echo"))
			{
				k = 1;
				while (b->arg[i + k] && b->arg[i + k][0] == '-' && b->arg[i + k][1] == 'n')
				{
					j = 2;
					while (b->arg[i + k])
					{
						if (b->arg[i + k][j] == 'n')
							j++;
						else
							break ;
					}
					printf("%d %d\n", j, px_strlen(b->arg[i + k]));
					if (j == px_strlen(b->arg[i + k]))
					{
						tmp = change_arg(b->arg[i + k], "-n");
						// tmp = new_arg;
						printf("tmp %s\n", tmp);
						free(b->arg[i + k]);
						b->arg[i + k] = tmp;
					}
					else
						break ;
					b->echo_n_cnt = k;
					k++;
				}
			}
			else
			{
				if (b->arg[i + 1] && px_strcmp(b->arg[i + 1], "-n"))
					b->echo_n_cnt = 1;
			}
		}
		printf("new b->arg[%d] = %s\n", i, b->arg[i]);
	}
	printf("k %d, -n cnt %d\n", k, b->echo_n_cnt);
}

void		check_arguments(t_all *a)
{
	int		i;
	int		j;
	t_all	*b;
	t_list	*head;

	b = a;
	while (b)
	{
		printf("\n->->-> split start point <-<-<-\n");
		b->cmd = NULL; // 초기화를 여기서 하지 않고 init에서 하면 세그폴트가 남 왜??
		b->arg = split_args(b->int_line_cut, b->line_cut, 2);		
		head = b->redir_list;
		i = -1;
		while (b->arg[++i])
		{
			if (b->redir_list->redir_flag != 0)
			{
				b->redir_list->next = make_next_flag_list(b);
				b->redir_list = b->redir_list->next;
			}
			j = 0;
			if (b->arg[i][j] == '>')
			{
				if (b->arg[i][j + 1] == '>' && b->arg[i][j + 2] == ' ')
				{
					j = j + 3;
					b->redir_list->redir_flag = 4;
				}
				else if (b->arg[i][j + 1] == ' ')
				{
					j = j + 2;
					b->redir_list->redir_flag = 2;
				}
				b->redir_list->file = ft_strdup(&b->arg[i][j]);
				b->arg[i][0] = '\0';
			}
			else if (b->arg[i][j] == '<')
			{
				if (b->arg[i][j + 1] == '<' && b->arg[i][j + 2] == ' ')
				{
					j = j + 3;
					b->redir_list->redir_flag = 3;
				}
				else if (b->arg[i][j + 1] == ' ')
				{
					j = j + 2;
					b->redir_list->redir_flag = 1;
				}
				b->redir_list->file = ft_strdup(&b->arg[i][j]);
				b->arg[i][0] = '\0';
			}
			else
			{
				if (i == 0)
					b->cmd = ft_strdup(b->arg[0]);
				else if (i > 0 && b->cmd == NULL)
					b->cmd = ft_strdup(b->arg[i]);
			}
		}
		b->redir_list = head;
		/* 잘 들어갔나 체크용 */
		printf("********* result *********\n");
		printf("b->cmd = |%s|\n", b->cmd);
		int k = 0;
		while (b->arg[k])
		{
			printf("arg[%d] %s\n", k, b->arg[k]);
			// printf("%d %s\n",b->redir_list->redir_flag, b->redir_list->file);
			while (b->redir_list)
			{
				printf("%d %s\n",b->redir_list->redir_flag, b->redir_list->file);
				b->redir_list = b->redir_list->next;
			}
			k++;
		}
		b->redir_list = head;
		/* 여기까지 지우기 */
		rearrange_arg(b);
		b = b->next;
	}
	printf("\n\n");
	// is_cmd_echo(a);
}
