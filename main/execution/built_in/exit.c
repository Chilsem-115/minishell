/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:38:43 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/25 19:49:37 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

static long	atoi_routine(char *s, t_context *ctx, int i, int r)
{
	int		digit;
	long	j;

	j = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = s[i] - '0';
		if (r == 1 && (j > (LLONG_MAX - digit) / 10))
		{
			ctx->var->max = 1;
			return (0);
		}
		if (r == -1 && (-j < (LLONG_MIN + digit) / 10))
		{
			ctx->var->max = 1;
			return (0);
		}
		j = j * 10 + digit;
		i++;
	}
	return (j);
}

long	long_atoi(char *s, t_context *ctx)
{
	int		i;
	long	j;
	int		r;

	i = 0;
	j = 0;
	r = 1;
	while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			r = -1;
		i++;
	}
	j = atoi_routine(s, ctx, i, r);
	return (j * r);
}

static int	number_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int len(char **args)
{
	int i = 0;

	while (args[i])
		i++;
	return (i);
}

void	exit_command(t_context *ctx, char **args)
{
	long	status;

	status = get_exit_status(0, 1);
	if (ctx->var->p != 1)
		ft_dprintf(2, "exit\n");
	if (args[1])
	{
		status = long_atoi(args[1], ctx);
		if (ctx->var->max == 1 || number_check(args[1]) == 1)
		{
			close(ctx->var->fd[0]);
			close(ctx->var->fd[1]);
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			ft_exit(2);
		}
	}
	if (len(args) >= 3)
		printf("bash: exit: too many arguments\n");
	else
	{
		close(ctx->var->fd[0]);
		close(ctx->var->fd[1]);
		ft_exit(status);
	}
}

long	get_exit_status(int st, int c)
{
	static long	status;

	if (c == 0)
		status = st;
	return (status);
}
