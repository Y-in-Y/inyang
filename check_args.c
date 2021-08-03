/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:17:22 by inyang            #+#    #+#             */
/*   Updated: 2021/08/04 01:43:13 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


void		check_arguments(t_all *a)
{
	int		i;
	int		j;
	t_all	*b;
	t_list	*head;

	b = a;
	while (b)
	{
		b->cmd = NULL;
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
}
