/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 02:01:30 by inyang            #+#    #+#             */
/*   Updated: 2021/08/18 17:44:24 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

extern t_env	*g_env_list;

char	*env_name_check(char *name)
{
	int		i;
	char	*e_name;

	i = 0;
	e_name = ft_strdup(name);
	while (name[i])
	{
		if (ft_isalpha(name[i]) == 1 || ft_isdigit(name[i]) == 1 || \
		name[i] == '_')
			i++;
		else
		{
			e_name[i] = '\0';
			break ;
		}
	}
	return (e_name);
}

char	*is_question(char *name)
{
	char	*e_name;

	if (name[0] == '?')
	{
		e_name = ft_itoa(g_env_list->exit_code);
		return (e_name);
	}
	return (0);
}

char	*find_env_value(char *name)
{
	t_env	*env;
	char	*e_name;

	env = g_env_list;
	e_name = is_question(name);
	if (e_name != NULL)
		return (e_name);
	e_name = env_name_check(name);
	while (env)
	{
		if (ft_strncmp(env->name, e_name, px_strlen(e_name)) == 1)
			break ;
		env = env->next;
	}
	free(e_name);
	if (env)
		return (env->value);
	else
		return (ft_strdup(""));
}
