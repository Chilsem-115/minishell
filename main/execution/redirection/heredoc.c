/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:02:49 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/26 00:03:23 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"

int			g_gsignum;

static int	name_file(char **file)
{
	int	fd_hd;

	*file = generate_full_path();
	fd_hd = open(*file, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd_hd < 0)
	{
		perror("open heredoc");
		ft_free(*file);
		return (false);
	}
	return (fd_hd);
}

static int	qout_check(char *s)
{
	if (ft_strchr(s, '\'') != 0 || ft_strchr(s, '\"') != 0)
		return (1);
	return (0);
}

static int	input_heredoc(char *s, int fd_hd, char *delimiter)
{
	if (!s)
	{
		ft_dprintf(2, "bash: warning: here-document )");
		ft_dprintf(2, "delimited by end-of-file (wanted `%s')\n", delimiter);
		close(fd_hd);
		return (1);
	}
	if (ft_strcmp(s, delimiter) != 0)
	{
		write(fd_hd, s, ft_strlen(s));
		write(fd_hd, "\n", 1);
	}
	else if (!g_gsignum)
	{
		close(fd_hd);
		return (1);
	}
	return (0);
}

bool	heredoc(char **list, t_context *ctx)
{
	int		fd_hd;
	int		r;
	char	*s;
	char	*delimiter;

	r = qout_check(*list);
	delimiter = remove_qouts(*list);
	fd_hd = name_file(list);
	while (g_gsignum == 0)
	{
		s = readline("> ");
		if (r == 0)
			s = expand_token_text(s, ctx);
		if (input_heredoc(s, fd_hd, delimiter) == 1)
			break ;
	}
	return (g_gsignum == 0);
}
