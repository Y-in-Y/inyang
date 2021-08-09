/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:11:14 by inyang            #+#    #+#             */
/*   Updated: 2021/08/10 00:52:43 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_env	*g_env_list;

void	line_to_changed(char *line, int *changed)
{
	int		i;

	i = 0;
	printf("line in %s\n", line);
	while (line[i])
	{
		if ((line[i] >= 'a' && line[i] <= 'z') || \
		(line[i] >= 'A' && line[i] <= 'Z'))
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
			i = redir_name(line, changed, i);
		else if (line[i] == '|')
			changed[i] = 8;
		else
			changed[i] = 9;
		if (i < 0)
			break ;
		i++;
	}
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
	struct_init(a);
	line_to_changed(line, changed);
	i = 0;
	while (line[i])
	{
		if (changed[i] == 1111111)
		{
			printf("line to change error\n");
			return ;
		}
		i++;
	}
	new_line = cutting_int_line(line, &changed, a);
	changed_line_cut(changed, a);
	check_arguments(a);
	printf("in parging_after check arguments\n");
	is_cmd_echo(a);
	t_all *b;
	b = a;
	while (b)
	{
		int i = -1;
		while (b->arg[++i])
			printf("this is final %s\n", b->arg[i]);
		b = b->next;
	}
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
	g_env_list = envp_to_list(envp[0]);
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
	printf("**********************************\n");
	printf("test1\n");
	line = "echo -n hi";
	parsing(line, &a);
	printf("test7\n");
	line = "echo \"$? $USER $PWD\"";
	parsing(line, &a);
/*
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
*/
	return (0);
}
