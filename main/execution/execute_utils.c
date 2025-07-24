
#include "messh.h"
#include "libft.h"
#include "execute.h"

void pwd()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	cwd[ft_strlen(cwd)] = '\0';
	printf("%s\n", cwd);
}

void exit_command(char **args)
{
	int status = 0;

	if(args[1])
		status = ft_atoi(args[1]);
	exit(status);
}

t_env *init_env(char **envp)
{
	t_env *head = NULL;
	t_env *node;
	int	i;

	i = 0;
	while (envp[i])
	{
		char **kv = split_once(envp[i], '=');
		node = malloc(sizeof(t_env));
		node->key = ft_strdup(kv[0]);
		if(kv[1])
			node->value = ft_strdup(kv[1]);
		else
			node->value = NULL;
		ft_envadd_back(&head, node);
		i++;
	}
	return head;
}

void	export_var(t_context *ctx, char *arg)
{
	char *eq = ft_strchr(arg, '=');
	if (!eq)
		return;

	char *key = ft_substr(arg, 0, eq - arg);
	char *value = ft_strdup(eq + 1);
	t_context *curr = ctx;

	while (curr)
	{
		if (!ft_strncmp(curr->envp->key, key, ft_strlen(key)))
		{
			free(curr->envp->value);
			curr->envp->value = value;
			free(key);
			return;
		}
		curr->envp = curr->envp->next;
	}
	// Add new var
	t_env *new = malloc(sizeof(t_context));
	new->envp->key = key;
	new->envp->value = value;
	new->envp->next = *env_list;
	*ctx = new;
}

void	unset_var(t_context *ctx, char *key)
{
	t_context	*curr;
	t_context	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->envp->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->envp->next = curr->envp->next;
			else
				*env_list = curr->envp->next;
			free(curr->envp->key);
			free(curr->envp->value);
			free(curr);
			return;
		}
		prev->envp = curr->envp;
		curr->envp = curr->envp->next;
	}
}
