/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:09:50 by inyang            #+#    #+#             */
/*   Updated: 2021/07/30 04:47:28 by inyang           ###   ########.fr       */
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
	int				exit_code;
	char			*name;
	char			*value;
	char			**origin;
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
	// int				*int_arg;
	int				echo_n_cnt;
	t_list			*redir_list;
	struct s_all	*next;
}					t_all;

t_env	*envp_to_list(char *env);
void	line_to_changed(char *line, int *changed, t_all *a);
char			**split_args(int *int_line, char *s, int c);
int				px_gnl(char **line);
int				px_strlen(char *s);
char	*px_strjoin(char *s1, char *s2);
int	ft_strncmp(char *dst, char *src, int size);
char	*ft_itoa(int n);
char	*find_env_value(char *name);
char	*cutting_int_line(char *line, int **i_int, t_all *a);
void			changed_line_cut(char *line, int *changed, t_all *a);
char			*ft_strdup(char *src);
t_list	*make_next_flag_list(t_all *a);
void		check_arguments(t_all *a);
void		is_cmd_echo(t_all *a);
void		is_there_env(t_all *a);
void		is_there_quote(t_all *a);
char		**split_args(int *int_line, char *s, int c);
static size_t	ft_cnt(int *s, int c, int strlen);
static int		ft_n_malloc(char **all, size_t k, size_t cnt);
static size_t	ft_index(size_t i, int *s, int c, int strlen);
void    rearrange_arg(t_all *a);
#endif