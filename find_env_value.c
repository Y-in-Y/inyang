#include "parsing.h"

extern t_env *g_env_list;

int	ft_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*find_env_value(char *name)
{
	t_env	*env;
	char	*e_name;
	int		i;

	env = g_env_list;
	e_name = ft_strdup(name);
	i = 0;
	if (name[0] == '?')
	{
		free(e_name);
		e_name = ft_itoa(g_env_list->exit_code); //need to edit
		printf("\n\n>>$? : %s<<\n\n", e_name);
		return (e_name);
	}
	while (name[i])
	{
		if (ft_isalpha(name[i]) == 1 || ft_isdigit(name[i]) == 1 || name[i] == '_')
			i++;
		else
		{
			e_name[i] = '\0';
			break ;
		}
	}
	printf("\n\nname : %s, e_name : %s\n\n", name, e_name);
	while (env)
	{
		if (ft_strncmp(env->name, e_name, px_strlen(e_name)) == 1)
			break;
		env = env->next;
	}
	free(e_name);
	if (env)
		return (env->value);
	return (0);
}
