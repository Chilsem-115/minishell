#include "../include/minishell.h"
#include "../Libft/libft.h"

void print_env(t_context *ctx)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void print_export(t_context *ctx)
{
	while (ctx->envp)
	{
		if (ctx->envp->value)
		{
			printf("declare -x ");
			printf("%s=%s\n", ctx->envp->key, ctx->envp->value);
		}
		ctx->envp = ctx->envp->next;
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

char **my_env(t_context	*ctx)
{
	int		i;
	int		n;
	char	**arr;
	t_context	*s;
	char	*str;

	s = ctx;
	i = 0;
	n = lenlist(*ctx->envp);
	arr = malloc(sizeof(char *) * (n + 1));
	while (s)
	{
		str = ft_strjoin(s->envp->key, "=");
		str = ft_strjoin(str, s->envp->value);
		arr[i] = str;
		s->envp = s->envp->next;
		i++;
		str = "\0";
	}
	return(arr);
}

char	*my_getenv(char *s, t_context *ctx)
{
	t_env *t;
	int	i;

	i = 0;
	while (s[i])
		i++;

	t = ctx->envp;
	while (t)
	{
		if (ft_strncmp(s, t->key, i) == 0)
			return (t->value);
		t = t->next;
	}
	return (NULL);
}

