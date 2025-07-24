#include "../include/minishell.h"
#include "../Libft/libft.h"

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

void export_var(t_env **env_list, char *arg)
{
	char *eq = ft_strchr(arg, '=');
	if (!eq)
		return;

	char *key = ft_substr(arg, 0, eq - arg);
	char *value = ft_strdup(eq + 1);
	t_env *curr = *env_list;

	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			free(curr->value);
			curr->value = value;
			free(key);
			return;
		}
		curr = curr->next;
	}
	// Add new var
	t_env *new = malloc(sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env_list;
	*env_list = new;
}

void unset_var(t_env **env_list, char *key)
{
	t_env *curr = *env_list;
	t_env *prev = NULL;

	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}