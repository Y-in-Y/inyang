/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 01:42:27 by inyang            #+#    #+#             */
/*   Updated: 2021/08/07 03:55:13 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	*change_env_name_to_value(int i, int j, char *new_line, int env_len, int *tmp)
{
	int	idx;
	int	*new_int;

	new_int = (int *)malloc(sizeof(int) * px_strlen(new_line));
	idx = 0;
	while (idx < i) // env 이전 int
	{
		new_int[idx] = tmp[idx];
		idx++;
	}
	while (idx < i + env_len) // env 가 있는 부분
	{
		new_int[idx] = 1;
		idx++;
	}
	i = idx;
	while (idx < px_strlen(new_line)) // env 끝난부분
	{
		new_int[idx] = tmp[j];
		j++;
		idx++;
	}
	return (new_int);
}

char	*insert_env_value(int i, int j, char *new_line, char *env_value, int env_len)
{
	char	*tmp_s;
	char	*l_tmp_s;


	new_line[i] == '\0';
	tmp_s = px_strjoin(new_line, env_value);
	l_tmp_s = ft_strdup(&new_line[j]);
	free(new_line);
	new_line = px_strjoin(tmp_s, l_tmp_s);
	free(tmp_s);
	free(l_tmp_s);
	return (new_line);
}

void	replace_env(char *new_line, int *tmp, int i)
{
	int		j;
	int		env_len;
	char	*new_line;
	char	*env_value;
	int		*new_int;

	j = i;
	while (new_line[j] && tmp[j] == 5)
		j++;
	printf("new_line[start] : %c, new_line[end] : %c\n", new_line[i], new_line[j - 1]);
	env_value = find_env_value(&new_line[i + 1]);
			// printf("env value is %s\n", env_value);
	env_len = px_strlen(env_value);
			// printf("env value is %s\n", env_value);
	if (env_value)
	{
		new_line = insert_env_value(i, j, new_line, env_value, env_len);
		free(tmp);
	}
	return (new_line);
}

char	*find_dollar_question(char *new_line, int *changed)
{
	int	i;
	int	*tmp;

	i = 0;
	tmp = changed;
	while (new_line && new_line[i])
	{
		if (tmp[i] == 5 && new_line[i] == '$' && new_line[i + 1] == '?')
			tmp[i + 1] = 5;
		i++;
	}
	return (tmp);
}

char	*env_to_str(char *line, int **changed)
{
	int		i;
	int		j;
	int		*tmp;
	int		*new_int;
	char	*new_line;
	char	*tmp_s;
	char	*env_value;
	int		env_len;
	char	*l_tmp_s;

	new_line = ft_strdup(line);
	tmp = find_dollar_question(new_line, *changed);
	i = 0;
	while (new_line && new_line[i])
	{
		tmp = *changed;
		if (new_line[i] && tmp[i] != 5)
			i++;
		else if (new_line[i] && tmp[i] == 5)
		{
			replace_env(new_line, tmp, i);
			j = i;
			while (new_line[j] && tmp[j] == 5)
				j++;
			printf("new_line[start] : %c, new_line[end] : %c\n", new_line[i], new_line[j - 1]);
			env_value = find_env_value(&new_line[i + 1]);
			// printf("env value is %s\n", env_value);
			env_len = px_strlen(env_value);
			// printf("env value is %s\n", env_value);
			if (env_value)
			{
				new_line[i] = '\0';
				printf("start to \'$\'start : |%s|\n", new_line);
				tmp_s = px_strjoin(new_line, env_value); //newline[0] ~ newline[i - 1] + env_value
				printf("start to \'$\'end : |%s|\n", tmp_s);
				l_tmp_s = ft_strdup(&new_line[j]);
				free(new_line);
				new_line = px_strjoin(tmp_s, l_tmp_s); // newline[0] ~ newline[i - 1] + env_value + newline[j] ~ end // newline[i] ~ newline[j - 1] 를 env_value 로 교체
				printf("start to end : |%s|\n", new_line);
				free(tmp_s);
				free(l_tmp_s);
				new_int = (int *)malloc(sizeof(int) * px_strlen(new_line));
				new_int = change_env_name_to_value(i, j, new_line, env_len, tmp);
				free(tmp);
				*changed = new_int;
			}
			else // value 못찾으면 $있어도 단순출력처립ㅂ
			{
				while (tmp[i] == 5)
				{
					tmp[i] = 1;
					i++; //hi >< 힛
				}
			}
		}
	}
	return (new_line);
}