/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:12:56 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/23 22:31:38 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"
#include <signal.h>
#include <sys/types.h>

char	**split_once(const char *str, char sep)
{
	char	**res;
	int		i;

	res = garbage_coll(0, sizeof(char *) * 3);
	i = 0;
	if (!res || !str)
		return (NULL);
	while (str[i] && str[i] != sep)
		i++;
	res[0] = ft_substr(str, 0, i);
	if (str[i] == sep)
		res[1] = ft_strdup((char *)(str + i + 1));
	else
		res[1] = NULL;
	res[2] = NULL;
	return (res);
}

char	*check_exec(char *s, t_context *ctx)
{
	int		i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split(my_getenv("PATH", ctx), ':');
	if (!str || !*str)
		return (s);
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, s);
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		{
			perror("bash");
			exit(126);
		}
		else if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int	exec_check(char *s)
{
	if (s[0] && (s[0] == '/' || (s[0] == '.' && s[1] == '/')))
		return (1);
	return (0);
}

void	*saved_signal(void *sig1, void *sig2, int f)
{
	static void	(*oldhdl_int)(int);
	static void	(*oldhdl_quit)(int);

	if (f == 0)
	{
		oldhdl_int = sig1;
		oldhdl_quit = sig2;
	}
	else if (f == 1)
		return (oldhdl_int);
	return (oldhdl_quit);
}

void close_fds(t_context *ctx)
{
	dup2(ctx->var->fd[0], 0);
	dup2(ctx->var->fd[1], 1);
	close(ctx->var->fd[0]);
	close(ctx->var->fd[1]);
}