extern t_env *g_env_list;

char	*find_env_value(char *name)
{
	t_env	*env;

	env = g_env_list;
	while (env)
	{
		if (ft_strncmp(env->name, name, ft_strlen(name)) == 1)
			break;
		env = env->next;
	}
	if (env)
		return (env->value);
	return (0);
}
