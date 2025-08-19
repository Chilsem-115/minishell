#include "messh.h"
#include "libft.h"
#include "execute.h"

t_env *init_env(char **envp)
{
	t_env *head;
	t_env *node;
	int	i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		char **kv = split_once(envp[i], '=');
		node = garbage_coll(0, sizeof(t_env));
		node->key = ft_strdup(kv[0]);
		if(kv[1])
			node->value = ft_strdup(kv[1]);
		else
			node->value = NULL;
		node->next = NULL;
		ft_envadd_back(&head, node);
		i++;
	}
	return head;
}

void	print_env(t_env *env)
{
	if(!env)
		return ;
	// printf("**\n");
	// printf("%p\n", env);
	// printf("key = %s --- value = %s\n", env->key, env->value);
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

char **my_env(t_context	*ctx)
{
	int		i;
	int		n;
	char	**arr;
	t_env	*s;
	char	*str;

	s = ctx->envp;
	i = 0;
	n = lenlist(ctx->envp);
	arr = garbage_coll(0, sizeof(char *) * (n + 1));
	while (s)
	{
		str = ft_strjoin(s->key, "=");
		str = ft_strjoin(str, s->value);
		arr[i] = str;
		s = s->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	*my_getenv(char *s, t_context *ctx)
{
	t_env	*t;
	int		i;

	i = 0;
	while (s[i])
		i++;
	t = ctx->envp;
	while (t)
	{
		if (ft_strncmp(s, t->key, i + 1) == 0)
			return (t->value);
		t = t->next;
	}
	return (NULL);
}

void ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

	if (!lst || !new)
		return;
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}