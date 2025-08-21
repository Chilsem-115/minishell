/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:14:21 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/21 15:44:03 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"
#include "libft.h"
#include "execute.h"

int	pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("pwd: error retrieving current directory: getcwd: cannot");
		printf("access parent directories: No such file or directory\n");
		return (1);
	}
	else
	{
		cwd[ft_strlen(cwd)] = '\0';
		printf("%s\n", cwd);
	}
	return (0);
}

static void	n_option(char **argv, int *i, int *f)
{
	int	j;

	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] == 'n')
	{
		j = 1;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != '\0')
			return ;
		*f = 1;
		(*i)++;
	}
}

void	echo_cmd(t_context *ctx, char **argv)
{
	int	i;
	int	f;

	(void) ctx;
	i = 1;
	f = 0;
	n_option(argv, &i, &f);
	while (argv[i])
	{
		ft_dprintf(1, "%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(1, " ");
		i++;
	}
	if (f == 0)
		ft_dprintf(1, "\n");
}

int	lenlist(t_env *env_list)
{
	t_env	*t;
	int		n;

	n = 0;
	t = env_list;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
