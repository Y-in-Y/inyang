/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:14:44 by inyang            #+#    #+#             */
/*   Updated: 2021/08/03 22:42:11 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_all	*make_next_page(void)
{
	t_all	*a;

	a = (t_all *)malloc(sizeof(t_all));
	a->redir_list = (t_list *)malloc(sizeof(t_list));
	a->next = NULL;
	a->redir_list->next = NULL;
	a->redir_list->redir_flag = 0;
	a->redir_list->file = NULL;
	return (a);
}

t_list	*make_next_flag_list(t_all *a)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	l->redir_flag = 0;
	l->file = NULL;
	l->next = NULL;
	return (l);
}

void	struct_init(t_all *a)
{
	a->redir_list = (t_list *)malloc(sizeof(t_list));
	a->pipe_cnt = 0;
	a->next = NULL;
	a->redir_list->next = NULL;
	a->redir_list->redir_flag = 0;
	a->redir_list->file = NULL;
}
