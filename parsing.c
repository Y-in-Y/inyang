/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:11:14 by inyang            #+#    #+#             */
/*   Updated: 2021/07/31 00:51:11 by ylee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*g_env_list;

int	left_name(char *line, int *changed, int i, t_all *a)
{
	if (line[i + 1] == ' ')
	{
		changed[i + 1] = 6;
		i = i + 2;
	}
	else if (line[i + 1] == '<' && line[i + 2] == ' ')
	{
		changed[i + 1] = 6;
		changed[i + 2] = 6;
		i = i + 3;
	}
	else
		return (-1);
	if (!line[i])
	{
		printf("redirection arg missing\n");
		return (-1);
	}
	while (line[i] && line[i] != ' ')
		changed[i++] = 6;
	return (i);
}

int	right_name(char *line, int *changed, int i, t_all *a)
{
	if (line[i + 1] == ' ')
	{
		changed[i + 1] = 7;
		i = i + 2;
	}
	else if (line[i + 1] == '>' && line[i + 2] == ' ')
	{
		changed[i + 1] = 7;
		changed[i + 2] = 7;
		i = i + 3;
	}
	else
		return (-1);
	if (!line[i])
	{
		printf("redirection arg missing\n");
		return (-1);
	}
	while (line[i] && line[i] != ' ')
		changed[i++] = 7;
	return (i);
}

int redir_name(char *line, int *changed, int i, t_all *a)
{
	if (line[i] == '<')
	{
		changed[i] = 6;
		i = left_name(line, changed, i, a);
	}
	else if (line[i] == '>')
	{
		changed[i] = 7;
		i = right_name(line, changed, i, a);
	}
	if (i < 0)
		printf("syntax error\n");
	return (i - 1);
}

int	env_name(char *line, int *changed, int i)
{
	changed[i] = 5;
	while (line[++i])
	{
		if ((line[i] >= 'A' && line[i] <= 'Z') ||
				(line[i] >= 'a' && line[i] <= 'z') ||
				(line[i] >= '0' && line[i] <= '9') ||
				(line[i] == '_'))
			changed[i] = 5;
		else
			break ;
	}
	return (i - 1);
}

int	s_quote(char *line, int *changed, int i)
{
	changed[i] = 4;
	while (line[++i])
	{
		if (line[i + 1] != '\'')
			changed[i] = 1;
		else if (line[i + 1] == '\'')
		{
			changed[i] = 1;
			changed[i + 1] = 4;
			i++;
			break;
		}
	}
	if (!line[i] && changed[i - 1] != 4)
		printf("syntax error\n");
	return (i);
}

int	d_quote(char *line, int *changed, int i)
{
	changed[i] = 3;
	while (line[++i])
	{
		if (line[i] == '$')
			i = env_name(line, changed, i);
		else if (line[i + 1] != '\"')
			changed[i] = 1;
		else if (line[i + 1] == '\"')
		{
			changed[i] = 1;
			changed[i + 1] = 3;
			i++;
			break;
		}
	}
	if (!line[i] && changed[i - 1] != 3)
		printf("syntax error\n");
	return (i);
}

void	line_to_changed(char *line, int *changed, t_all *a)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
			changed[i] = 0;
		else if (line[i] == ' ' || line[i] == '\t')
			changed[i] = 2;
		else if (line[i] == '\"')
			i = d_quote(line, changed, i);
		else if (line[i] == '\'')
			i = s_quote(line, changed, i);
		else if (line[i] == '$')
			i = env_name(line, changed, i);
		else if (line[i] == '<' || line[i] == '>')
			i = redir_name(line, changed, i, a);
		else if (line[i] == '|') 
			changed[i] = 8;
		else 
			changed[i] = 9;
		if (i < 0)
			break ;
		i++;
	}
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
	// a->cmd = NULL;
	// a->redir_list->prev = NULL;
	a->redir_list->next = NULL;
	a->redir_list->redir_flag = 0;
	a->redir_list->file = NULL;
}

void	parsing(char *line, t_all *a)
{
	int		i;
	int		*changed;
	int		length;
	char	*new_line;

	length = px_strlen(line);
	changed = (int *)malloc(sizeof(int) * length);
	i = 0;
	while (i < length)
		changed[i++] = 1111111;
	printf("%s\n", line);
	struct_init(a);
	line_to_changed(line, changed, a);
	i = 0;
	while (line[i])
	{
		if (changed[i] == 1111111)
			return ;
		printf("%d", changed[i]);
		i++;
	}
	printf("\n");
	new_line = cutting_int_line(line, &changed, a);
	changed_line_cut(new_line, changed, a);
	printf(">>> cut here <<<");
	check_arguments(a);
	is_cmd_echo(a);
	// is_there_quote(a);
	// is_there_env(a);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*list;
	t_all	a;
	int		i;

	if (argc != 1 || !argv || !envp)
		return (0);
	i = 0;
	g_env_list= envp_to_list(envp[0]);
	g_env_list->origin = envp;
	g_env_list->exit_code = 0;
	list = g_env_list;
	i = 1;
	while (envp && envp[i])
	{
		list->next = envp_to_list(envp[i]);
		list = list->next;
		i++;
	}
	printf("test value : %s\n", g_env_list->next->value);
	printf("***$?******$?******$?******$?*************\n");
	printf("$??\n");
	g_env_list->exit_code = 127;
	line = "echo $? \'$PWD is $? here\' and \"$PWD is $? here\" | cat << $? | wc -l $?";
	parsing(line, &a);
/*
	printf("**********************************\n");
	printf("test1\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ylee | wc -l";
	parsing(line, &a);
	printf("**********************************\n");
	printf("\n\n\n\ntest2\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ylee";
	parsing(line, &a);
	printf("**********************************\n");	
	printf("\n\n\n\n\ntest3\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ";
	parsing(line, &a);
	// system("leaks a.out");
	// printf("**********************************\n");
	printf("\n\n\n\n\ntest4\n");
	line = "echo \"test1\" \"test2\"";
	parsing(line, &a);
	// printf("test5\n");
	// line = "< main.c echo test";
	// parsing(line, &a);
	// printf("test6\n");
	// line = "echo $PWD $? where$PWD";
	// parsing(line, &a);
	// printf("test7\n");
	// line = "< in ecHo << cat -n -nnn -n a >> out";
	// parsing(line, &a);
*/
	return (0);
}
