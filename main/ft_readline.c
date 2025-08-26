/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 05:19:04 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 05:19:41 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"
#include "execute.h"

extern int	g_gsignum;

static int	readline_checker(char *s, char *prompt)
{
	if (!s)
	{
		ft_free(s);
		ft_dprintf(2, "exit\n");
		ft_free(prompt);
		ft_exit(get_exit_status(0, 1));
	}
	if (g_gsignum == 2)
	{
		ft_free(s);
		return (1);
	}
	return (0);
}

char	*ft_readline(void)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*prompt;
	char	*s;

	cwd[0] = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_strjoin(C_OLIVE "enigma@minishell:", cwd);
	prompt = ft_strjoin(tmp, C_RESET "$ ");
	ft_free(tmp);
	while (1)
	{
		g_gsignum = 0;
		s = readline(prompt);
		if (readline_checker(s, prompt) == 1)
			continue ;
		if (s && *s)
			add_history(s);
		break ;
	}
	ft_free(prompt);
	return (s);
}
