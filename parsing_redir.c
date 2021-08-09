/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:02:36 by inyang            #+#    #+#             */
/*   Updated: 2021/08/09 14:37:11 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	left_name(char *line, int *changed, int i)
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

int	right_name(char *line, int *changed, int i)
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

int	redir_name(char *line, int *changed, int i)
{
	if (line[i] == '<')
	{
		changed[i] = 6;
		i = left_name(line, changed, i);
	}
	else if (line[i] == '>')
	{
		changed[i] = 7;
		i = right_name(line, changed, i);
	}
	if (i < 0)
		printf("syntax error\n");
	return (i - 1);
}
