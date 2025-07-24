
#include "execution.h"

t_env	*init_env(char **envp)
{
	char	*kv;
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		kv = split_once(envp[i], '=');
		node = malloc(sizeof(t_env));
		node->key = ft_strdup(kv[0]);
		if (kv[1])
			node->value = ft_strdup(kv[1]);
		else
			node->value = NULL;
		ft_envadd_back(&head, node);
		i++;
	}
	return (head);
}
