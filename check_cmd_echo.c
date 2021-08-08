/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 01:21:15 by inyang            #+#    #+#             */
/*   Updated: 2021/08/09 00:52:35 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*change_arg(char *s1, char *s2)
{
	int		i;
	char	*buf;

	buf = malloc(sizeof(char) * (px_strlen(s2) + 1));
	i = 0;
	while (s2[i])
	{
		buf[i] = s2[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

int	check_serial_n_option(t_all *b, int i, int k)
{
	int		j;

	j = 2;
	while (b->arg[i + k])
	{
		if (b->arg[i + k][j] == 'n')
			j++;
		else
			break ;
	}
	return (j);
}

void	if_cmd_lower_echo(t_all *b, int i)
{
	int		k;
	int		j;
	char	*tmp;

	k = 1;
	while (b->arg[i + k] && b->arg[i + k][0] == '-' && b->arg[i + k][1] == 'n')
	{
		j = check_serial_n_option(b, i, k);
		if (j == px_strlen(b->arg[i + k]))
		{
			tmp = change_arg(b->arg[i + k], "-n");
			free(b->arg[i + k]);
			b->arg[i + k] = tmp;
		}
		else
			break ;
		b->echo_n_cnt = k;
		k++;
	}
}

int	compare_cmd_echo(t_all *b, int i)
{
	if ((b->arg[i][0] == 'e' || b->arg[i][0] == 'E')
		&& (b->arg[i][1] == 'c' || b->arg[i][1] == 'C')
		&& (b->arg[i][2] == 'h' || b->arg[i][2] == 'H')
		&& (b->arg[i][3] == 'o' || b->arg[i][3] == 'O'))
		return (1);
	else
		return (0);
}

void	is_cmd_echo(t_all *a)
{
	t_all	*b;
	char	*tmp;
	int		i;

	b = a;
	printf("is_cmd_echo start\n");
	while (b)
	{
		if (b->cmd)
		{
			tmp = b->arg[1];
			b->echo_n_cnt = 0;
			i = -1;
			printf("is_cmd_echo start while\n");
			while (b->arg[++i])
			{
				if (compare_cmd_echo(b, i) == 1)
				{
					if (px_strcmp(b->cmd, "echo")) // 소문자로만 echo 인 경우
						if_cmd_lower_echo(b, i);
					else //ㄷㅐ소문자 섞인경우
					{
						if (b->arg[i + 1] && px_strcmp(b->arg[i + 1], "-n"))
							b->echo_n_cnt = 1;
					}
					printf(" -n cnt %d\n", b->echo_n_cnt); //지우기
				}
				printf("new b->arg[%d] = %s\n", i, b->arg[i]); //지우기
			}
		}
		b = b->next;
	}
}
