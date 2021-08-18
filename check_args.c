/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:17:22 by inyang            #+#    #+#             */
/*   Updated: 2021/08/19 01:09:02 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	put_cmd_in_struct(t_all *b, int i)
{
	if (i == 0)
		b->cmd = ft_strdup(b->arg[0]);
	else if (i > 0 && b->cmd == NULL)
		b->cmd = ft_strdup(b->arg[i]);
}

int	redir_flag_l(t_all *b, int i, int j)
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
	return (j);
}

int	redir_flag_r(t_all *b, int i, int j)
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
	return (j);
}

void	put_cmd_and_redir_flag(t_all *b, int i)
{
	int	j;

	if (b->redir_list->redir_flag != 0)
		make_new_flag_list(b);
	j = 0;
	if (b->arg[i][j] == '>')
		redir_flag_r(b, i, j);
	else if (b->arg[i][j] == '<')
		redir_flag_l(b, i, j);
	else
		put_cmd_in_struct(b, i);
}

void	check_arguments(t_all *a)
{
	int		i;
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
			put_cmd_and_redir_flag(b, i);
		b->redir_list = head;
		rearrange_arg(b);
		b = b->next;
	}
}
