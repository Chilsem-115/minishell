/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 22:44:24 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/26 03:39:43 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"
#include <signal.h>
#include <sys/types.h>

static	char	*ft_path(char **str, char *s, int i)
{
	char	*path;

	path = ft_strjoin(str[i], "/");
	path = ft_strjoin(path, s);
	return (path);
}

char	*check_exec(char *s, t_context *ctx)
{
	int		i;
	char	**str;
	char	*path;
	char	*fpath;

	i = 0;
	fpath = NULL;
	str = ft_split(my_getenv("PATH", ctx), ':');
	if (!str || !*str)
		return (s);
	while (str[i])
	{
		path = ft_path(str, s, i);
		if (is_dir(path) != 0)
		{
			i++;
			continue ;
		}
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
			fpath = path;
		else if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (fpath);
}

int	exec_check(char *s)
{
	if (s[0] && (s[0] == '/' || (s[0] == '.' && s[1] == '/')))
		return (1);
	return (0);
}

bool	check(t_context *ctx)
{
	if (!ctx->var->argv || !ctx->var->argv[0])
		return (false);
	if (exec_check(ctx->var->argv[0]) == 1)
	{
		execve(ctx->var->argv[0], ctx->var->argv, my_env(ctx));
		if (is_dir(ctx->var->argv[0]) != 0)
		{
			ft_dprintf(2, "bash: %s: Is a directory\n", ctx->var->argv[0]);
			ft_exit(127);
		}
		ft_dprintf(2, "%s: No such file or directory\n", ctx->var->argv[0]);
		ft_exit(127);
	}
	ctx->var->path = check_exec(ctx->var->argv[0], ctx);
	if (!ctx->var->path)
	{
		ft_dprintf(2, "%s: command not found\n", ctx->var->argv[0]);
		ft_exit(127);
	}
	return (true);
}
