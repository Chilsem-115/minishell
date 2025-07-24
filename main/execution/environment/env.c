#include "../include/minishell.h"
#include "../Libft/libft.h"

void print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void print_export(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			printf("declare -x ");
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
}

int lenlist(t_env *env_list)
{
	t_env *t;
	int	n;

	n = 0;
	t = env_list;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}

char **my_env(t_env **list_env)
{
	int		i;
	int		n;
	char	**arr;
	t_env	*s;
	char	*str;

	s = *list_env;
	i = 0;
	n = lenlist(*list_env);
	arr = malloc(sizeof(char *) * (n + 1));
	while (s)
	{
		str = ft_strjoin(s->key, "=");
		str = ft_strjoin(str, s->value);
		arr[i] = str;
		s = s->next;
		i++;
		str = "\0";
	}
	return(arr);
}

char	*my_getenv(char *s, t_env *list)
{
	t_env *t;
	int	i;

	i = 0;
	while (s[i])
		i++;
	
	t = list;
	while (t)
	{
		if (ft_strncmp(s, t->key, i) == 0)
			return (t->value);
		t = t->next;
	}
	return (NULL);
}
