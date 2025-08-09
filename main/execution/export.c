#include "messh.h"
#include "execute.h"

void update_var(t_env **list, char *key, char *value)
{
	t_env *curr;
	
	curr= *list;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			free(curr->value);
			curr->value = value;
			// free(key);
			return;
		}
		curr = curr->next;
	}
}

void valid_export(char *key, char *value)
{
	int i;
	if((key[0] > 'z' || key[0] < 'a') && (key[0] > 'Z' || key[0] < 'A') && key[0] != '_')
	{
		ft_dprintf(2, "bash: export: `%s=%s': not a valid identifier\n", key, value);
		return ;
	}//need handl "key"=value ou 'key'=value
	i = 1;
	while (key[i])
	{
		if (key[i] == '+' && key[i + 1] == '\0')
		{
			key[i] = '\0';
			i++;
		}
		else if ((key[i] > 'z' || key[i] < 'a') && (key[i] > 'Z' || key[i] < 'A') && key[i] != '_' && (key[i] > '9' || key[i] < '0'))
		{
			ft_dprintf(2, "bash: export: not a valid identifier\n", key, value);
			return ;
		}
		i++;
	}
}

void	export_var(t_env **env_list, char *arg)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*new;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return;
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	valid_export(key, value);
	update_var(env_list, key, value);
	new = garbage_coll(0, sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env_list;
	*env_list = new;
}

void print_export(t_context *ctx)
{
	t_env	*env;

	env = ctx->envp;
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