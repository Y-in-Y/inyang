/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:09:50 by inyang            #+#    #+#             */
/*   Updated: 2021/07/22 16:40:55 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_list  // 아무것도 없으면 0 / < 1 / > 2 / << 3 / >> 4
{
	int				redir_flag;
	char			*file;
	struct s_list	*next;
}					t_list;

typedef	struct		s_all{
	char			*line_cut;
	int				*int_line_cut;
	int				pipe_cnt;
	char			*cmd;
	char			**arg;
	int				echo_n_cnt;
	t_list			*redir_list;
	struct s_all	*next;
}					t_all;

char			**split_args(int *int_line, char *s, int c);
int				px_gnl(char **line);
int				px_strlen(char *s);
void			cutting_int_line(char *line, int *changed, t_all *a);
void			changed_line_cut(char *line, int *changed, t_all *a);
char			*ft_strdup(const char *src);
t_list	*make_next_flag_list(t_all *a);
void		check_arguments(t_all *a);
void		is_cmd_echo(t_all *a);
void		is_there_env(t_all *a);
#endif