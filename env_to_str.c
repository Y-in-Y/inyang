/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:42:27 by inyang            #+#    #+#             */
/*   Updated: 2021/08/09 01:01:55 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	*change_env_name_to_value(int *i, char *new_line, int env_len, int *tmp)
{
	int	idx;
	int	*new_int;

	new_int = (int *)malloc(sizeof(int) * px_strlen(new_line));
	idx = 0;
	while (idx < i[0])
	{
		new_int[idx] = tmp[idx];
		idx++;
	}
	while (idx < i[0] + env_len)
	{
		new_int[idx] = 1;
		idx++;
	}
	i[0] = idx;
	while (idx < px_strlen(new_line))
	{
		new_int[idx] = tmp[i[1]];
		i[1]++;
		idx++;
	}
	return (new_int);
}

char	*insert_env_value(int *i, char *new_line, char *env_value, int env_len)
{
	char	*tmp_s;
	char	*l_tmp_s;

	new_line[i[0]] = '\0';
	tmp_s = px_strjoin(new_line, env_value);
	l_tmp_s = ft_strdup(&new_line[i[1]]);
	free(new_line);
	new_line = px_strjoin(tmp_s, l_tmp_s);
	free(tmp_s);
	free(l_tmp_s);
	return (new_line);
}

void	find_dollar_question(char *new_line, int **changed)
{
	int	i;
	int	*tmp;

	i = 0;
	tmp = *changed;
	while (new_line && new_line[i])
	{
		if (tmp[i] == 5 && new_line[i] == '$' && new_line[i + 1] == '?')
			tmp[i + 1] = 5;
		i++;
	}
	*changed = tmp;
}

int	*return_final_line(int *i, char *env_value, char **tmp_str, int *tmp)
{
	int		*new_int;
	int		env_len;
	char	*new_line;

	new_line = *tmp_str;
	env_len = px_strlen(env_value);
	if (env_value)
	{
		new_line = insert_env_value(i, new_line, env_value, env_len);
		new_int = change_env_name_to_value(i, new_line, env_len, tmp);
		*tmp_str = new_line;
		free(tmp);
		return (new_int);
	}
	else
	{
		while (tmp[i[0]] == 5)
		{
			tmp[i[0]] = 1;
			i[0]++;
		}
		return (tmp);
	}
}

char	*env_to_str(char *line, int **changed)
{
	int		i[2];
	int		*tmp;
	char	*new_line;
	char	*env_value;

	new_line = ft_strdup(line);
	find_dollar_question(new_line, changed);
	i[0] = 0;
	while (new_line && new_line[i[0]])
	{
		tmp = *changed;
		if (new_line[i[0]] && tmp[i[0]] != 5)
			i[0]++;
		else if (new_line[i[0]] && tmp[i[0]] == 5)
		{
			i[1] = i[0];
			while (new_line[i[1]] && tmp[i[1]] == 5)
				i[1]++;
			env_value = find_env_value(&new_line[i[0] + 1]);
			*changed = return_final_line(i, env_value, &new_line, tmp);
		}
	}
	return (new_line);
}
