/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:51:40 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/22 16:05:42 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

int	update_var(t_env **list, char *key, char *value, int k)
{
	t_env	*curr;
	t_env	*new;

	curr = *list;
	if (!value)
		value = ft_strdup("\0");
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			free(curr->value);
			curr->value = value;
			return (1);
		}
		curr = curr->next;
	}
	if (k == 0)
	{
		new = garbage_coll(0, sizeof(t_env));
		new->key = key;
		new->value = value;
		new->next = *list;
		*list = new;
	}
	return (0);
}

void	valid_export(char *key, char *value)
{
	int	i;

	if ((key[0] > 'z' || key[0] < 'a') && (key[0] > 'Z' || key[0] < 'A')
		&& key[0] != '_')
	{
		ft_dprintf(2, "bash: export: `%s=%s'", key, value);
		(ft_dprintf(2, ": not a valid identifier\n"));
		return ;
	}
	i = 1;
	while (key[i])
	{
		if (key[i] == '+' && key[i + 1] == '\0')
		{
			key[i++] = '\0';
		}
		else if (!ft_isalnum(key[i]) && key[i] != '_')
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
		return ;
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	valid_export(key, value);
	if ((update_var(env_list, key, value, 1)) == 1)
		return ;
	new = garbage_coll(0, sizeof(t_env));
	new->key = key;
	new->value = value;
	new->next = *env_list;
	*env_list = new;
}

void	print_export(t_context *ctx)
{
	t_env	*env;

	env = ctx->envp;
	while (env)
	{
		if (env->value)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", env->key, env->value);
		}
		env = env->next;
	}
}
