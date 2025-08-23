/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:32:35 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/23 15:35:29 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

static int	cd_cmd(t_context *ctx, char *argv)
{
	char	cwd[PATH_MAX];

	cwd[0] = 0;
	getcwd(cwd, sizeof(cwd));
	if (!argv)
	{
		if (my_getenv("HOME", ctx) == NULL || chdir(my_getenv("HOME", ctx)) == -1)
		{
			ft_dprintf(2, "enigma: cd: HOME not set\n");
			return (1);
		}
	}
	else
	{
		if (chdir(argv) == -1)
		{
			ft_dprintf(2, "cd: No such file or directory\n");
			return (1);
		}
	}
	update_var(&ctx->envp, "OLDPWD", ft_strdup(my_getenv("PWD", ctx)), 0);
	update_var(&ctx->envp, "PWD", ft_strdup(getcwd(cwd, sizeof(cwd))), 0);
	return (0);
}

void	unset_var(t_env **env_list, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	ft_export(t_context *ctx, char **argv)
{
	int	i;

	if (!argv[1])
	{
		print_export(ctx);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		export_var(&ctx->envp, argv[i]);
		i++;
	}
}

static void	ft_unset(t_context *ctx, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		unset_var(&ctx->envp, argv[i]);
		i++;
	}
}

int	handle_builtin(t_context *ctx)
{
	char	**argv;
	int		stat;

	stat = 0;
	argv = ctx->ast->data.cmd.text;
	if (!argv)
		return (0);
	if (!ft_strncmp(argv[0], "cd", 3))
		stat = cd_cmd(ctx, argv[1]);
	else if (!ft_strncmp(argv[0], "exit", 5))
		exit_command(ctx, argv);
	else if (!ft_strncmp(argv[0], "export", 7))
		ft_export(ctx, argv);
	else if (!ft_strncmp(argv[0], "unset", 6) && argv[1])
		ft_unset(ctx, argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		print_env(ctx->envp);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		stat = pwd();
	else if (!ft_strncmp(argv[0], "echo", 5))
		echo_cmd(ctx, argv);
	else
		return (0);
	get_exit_status(stat, 0);
	return (1);
}
