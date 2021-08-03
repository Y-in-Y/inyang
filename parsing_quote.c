/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:04:54 by inyang            #+#    #+#             */
/*   Updated: 2021/08/03 22:41:59 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
			break ;
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
			break ;
		}
	}
	if (!line[i] && changed[i - 1] != 3)
		printf("syntax error\n");
	return (i);
}
