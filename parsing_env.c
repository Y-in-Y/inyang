/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:04:46 by inyang            #+#    #+#             */
/*   Updated: 2021/08/10 00:56:52 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	env_name(char *line, int *changed, int i)
{
	changed[i] = 5;
	while (line[i++])
	{
		if ((line[i] >= 'A' && line[i] <= 'Z') || \
		(line[i] >= 'a' && line[i] <= 'z') || \
		(line[i] >= '0' && line[i] <= '9') || \
		(line[i] == '_'))
			changed[i] = 5;
		else
			break ;
	}
	return (i - 1);
}
