/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:09:50 by inyang            #+#    #+#             */
/*   Updated: 2021/08/03 23:15:53 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_env
{
	int				exit_code;
	char			*name;
	char			*value;
	char			**origin;
	struct s_env	*next;
}					t_env;

typedef struct s_list// 아무것도 없으면 0 / < 1 / > 2 / << 3 / >> 4
{
	int				redir_flag;
	char			*file;
	struct s_list	*next;
}					t_list;

typedef struct s_all
{
	char			*line_cut;
	int				*int_line_cut;
	int				pipe_cnt;
	char			*cmd;
	char			**arg;
	int				echo_n_cnt;
	t_list			*redir_list;
	struct s_all	*next;
}					t_all;

//envp_to_list.c
t_env			*envp_to_list(char *env);
//parsing.c
void			parsing(char *line, t_all *a);
void			line_to_changed(char *line, int *changed, t_all *a);
//parsing_env.c
int				env_name(char *line, int *changed, int i);
//parsing_quote.c
int				s_quote(char *line, int *changed, int i);
int				d_quote(char *line, int *changed, int i);
//parsing_redir.c
int				redir_name(char *line, int *changed, int i, t_all *a);
int				right_name(char *line, int *changed, int i, t_all *a);
int				left_name(char *line, int *changed, int i, t_all *a);
//parsing_init.c
void			struct_init(t_all *a);
t_list			*make_next_flag_list(t_all *a);
t_all			*make_next_page(void);
//env_to_str.c
char			*env_to_str(char *line, int **changed);
//cutting_line.c
char			*cutting_int_line(char *line, int **i_int, t_all *a);
void			changed_line_cut(char *line, int *changed, t_all *a);
//split_line_by_two.c
char			**split_args(int *int_line, char *s, int c);
//parsing_utils.c
int				px_strlen(char *s);
char			*ft_strdup(char *src);
char			*px_strjoin(char *s1, char *s2);
int				ft_isdigit(char c);
int				ft_isalpha(char c);
//parsing_utils_2.c
int				ft_strncmp(char *dst, char *src, int size);
int				px_strcmp(char *dst, char *src);
char			*ft_itoa(int n);
//find_env_value.c
char			*find_env_value(char *name);
char			*is_question(char *name);
char			*env_name_check(char *name);
//check_args.c
void			check_arguments(t_all *a);
void			is_cmd_echo(t_all *a);
void			is_there_env(t_all *a);
void			is_there_quote(t_all *a);
char			**split_args(int *int_line, char *s, int c);
static size_t	ft_cnt(int *s, int c, int strlen);
static int		ft_n_malloc(char **all, size_t k, size_t cnt);
static size_t	ft_index(size_t i, int *s, int c, int strlen);
void			rearrange_arg(t_all *a);
#endif