/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:09:50 by inyang            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/10 01:06:05 by inyang           ###   ########.fr       */
=======
/*   Updated: 2021/08/10 00:38:42 by ylee             ###   ########.fr       */
>>>>>>> e9c607f88b1f671375113f9cea95a4b374643f27
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <term.h>
// # include "minishell.h"

typedef struct s_env
{
	int				exit_code;
	struct termios	backup;
	int				origin_stdin;
	int				origin_stdout;
	char			*name;
	char			*value;
	char			**origin;
	struct s_env	*next;
}					t_env;

typedef struct s_list// 아무것도 없으면 0 / < 1 / > 2 / << 3 / >> 4
{
	int				pipe_idx;
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
void			line_to_changed(char *line, int *changed);
//parsing_env.c
int				env_name(char *line, int *changed, int i);
//parsing_quote.c
int				s_quote(char *line, int *changed, int i);
int				d_quote(char *line, int *changed, int i);
//parsing_redir.c
int				redir_name(char *line, int *changed, int i);
int				right_name(char *line, int *changed, int i);
int				left_name(char *line, int *changed, int i);
//parsing_init.c
void			struct_init(t_all *a);
t_list			*make_next_flag_list(void);
t_all			*make_next_page(void);
void			make_new_flag_list(t_all *b);
//split_line_by_two.c
char			**split_args(int *int_line, char *s, int c);
int				ft_fill(int *int_line, char const *s, int c, char **all);
size_t			ft_cnt(int *s, int c, int strlen);
int				ft_n_malloc(char **all, size_t k, size_t cnt);
size_t			ft_index(size_t i, int *s, int c, int strlen);
//env_to_str.c
char			*env_to_str(char *line, int **changed);
void			find_dollar_question(char *new_line, int **changed);
int				*return_final_line(int *i, char *env_value, \
				char **tmp_str, int *tmp);
char			*insert_env_value(int *i, char *new_line, char *env_value);
int				*change_env_name_to_value(int *i, char *new_line, \
				int env_len, int *tmp);
//cutting_line.c
char			*cutting_int_line(char *line, int **i_int, t_all *a);
int				init_int_val(char *line_dup, int *idx);
int				split_by_pipe(t_all *b, t_all *a, int *idx, char *line_dup);
void			changed_line_cut(int *changed, t_all *a);
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
long long		make_num_plus(int n);
//find_env_value.c
char			*find_env_value(char *name);
char			*is_question(char *name);
char			*env_name_check(char *name);
//check_args.c
void			check_arguments(t_all *a);
void			put_cmd_and_redir_flag(t_all *b, int i);
int				redir_flag_r(t_all *b, int i, int j);
int				redir_flag_l(t_all *b, int i, int j);
void			put_cmd_in_struct(t_all *b, int i);
//check_cmd_echo.c
void			is_cmd_echo(t_all *a);
int				compare_cmd_echo(t_all *b, int i);
void			if_cmd_lower_echo(t_all *b, int i);
int				check_serial_n_option(t_all *b, int i, int k);
char			*change_arg(char *s2);
//rearrange_args.c
void			rearrange_arg(t_all *a);
int				count_args(t_all *a);
#endif
