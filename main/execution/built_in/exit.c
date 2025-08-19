/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:38:43 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/19 21:44:13 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"
#include "execute.h"

static long	atoi_routine(char *s, t_context *ctx, int i, int r)
{
	int		digit;
	long	j;

	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = s[i] - '0';
		if (r == 1 && (j > (LLONG_MAX - digit) / 10))
		{
			ctx->max = 1;
			return (0);
		}
		if (r == -1 && (-j < (LLONG_MIN + digit) / 10))
		{
			ctx->max = 1;
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

void	exit_command(t_context	*ctx, char **args)
{
	long	status;

	status = get_exit_status(0, 1);
	if (ctx->p != 1)
		printf("exit\n");
	if (args[1])
	{
		status = long_atoi(args[1], ctx);
		if (ctx->max == 1 || number_check(args[1]) == 1)
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
	}
	if (args[2])
		printf("bash: exit: too many arguments\n");
	else
		exit(status);
}

long	get_exit_status(int st, int c)
{
	static long	status;

	if (c == 0)
		status = st;
	return (status);
}
