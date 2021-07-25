/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:11:14 by inyang            #+#    #+#             */
/*   Updated: 2021/07/26 02:20:29 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	length = px_strlen(line);
	changed = (int *)malloc(sizeof(int) * length);
	i = 0;
	while (i < length)
		changed[i++] = 1111111;
	printf("%s\n", line);
	// printf("%d\n", length);
	struct_init(a);
	line_to_changed(line, changed, a);
	// printf("fin?\n");
	i = 0;
	// printf("%s\n", line);
	while (line[i])
	{
		if (changed[i] == 1111111)
			return ;
		printf("%d", changed[i]);
		i++;
	}
	printf("\n");
	cutting_int_line(line, changed, a);
	changed_line_cut(line, changed, a);
	check_arguments(a);
	is_cmd_echo(a);
	is_there_quote(a);
	// is_there_env(a);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_all	a;

	if (argc != 1 || !argv || !envp)
		return (0);
//	struct_init(&a);
	// printf("test1\n");
	// line = "hello \"inyang\". I`m \'ylee\'. good bye~ $PWD";
	// parsing(line);
	printf("**********************************\n");
	printf("test1\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ylee | wc -l";
	parsing(line, &a);
	printf("**********************************\n");
	printf("test2\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ylee";
	parsing(line, &a);
	printf("**********************************\n");	
	printf("\n\n\n\n\ntest3\n");
	line = "echo \'$PWD is here\' and \"$PWD is here\" | cat << ";
	parsing(line, &a);
	// system("leaks a.out");
	// printf("**********************************\n");
	printf("test4\n");
	line = "\"here is new example 'omg'\"";
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
	return (0);
}
