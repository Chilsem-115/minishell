/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:02:49 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/25 03:42:25 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"

int	g_gsignum;

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*generate_heredoc_filename(int i, int fd)
{
	const char		charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY\
	Z0123456789";
	char			random_part[9];
	unsigned char	byte;
	char			*filename;

	while (i < 8)
	{
		if (read(fd, &byte, 1) != 1)
		{
			close(fd);
			return (NULL);
		}
		random_part[i] = charset[byte % (sizeof(charset) - 1)];
		i++;
	}
	random_part[8] = '\0';
	close(fd);
	filename = garbage_coll(0, 8 + 1);
	if (!filename)
		return (NULL);
	strcpy(filename, random_part);
	return (filename);
}

char	*generate_full_path(void)
{
	int		fd;
	char	*name;
	char	*full_path;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (NULL);
	name = generate_heredoc_filename(0, fd);
	if (!name)
		return (NULL);
	full_path = garbage_coll(0, strlen("/tmp/") + strlen(name) + 1);
	if (!full_path)
	{
		free(name);
		return (NULL);
	}
	ft_strcpy(full_path, "/tmp/");
	ft_strcat(full_path, name);
	free(name);
	return (full_path);
}

static int	name_file(char	**file)
{
	int		fd_hd;

	*file = generate_full_path();
	fd_hd = open(*file, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd_hd < 0)
	{
		perror("open heredoc");
		free(*file);
		return (false);
	}
	return (fd_hd);
}
static int qout_check(char *s)
{
	if(ft_strchr(s, '\'') != 0 || ft_strchr(s, '\"') != 0)
		return (1);
	return (0);
}
bool	heredoc(char **list, t_context *ctx)
{
	int		fd_hd;
	int		r;
	char	(*s),(*delimiter);

	r = qout_check(*list);
	delimiter = remove_qouts(*list);
	fd_hd = name_file(list);
	while (g_gsignum == 0)
	{
		s = readline("> ");
		if(r == 0)
			s = expand_token_text(s, ctx);
		if(!s)
		{
			ft_dprintf(2, "bash: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			close(fd_hd);
			break;
		}
		if (ft_strcmp(s, delimiter) != 0)
		{
			write(fd_hd, s, ft_strlen(s));
			write(fd_hd, "\n", 1);
		}
		else if (!g_gsignum)
		{
			close(fd_hd);
			break ;
		}
	}
	return (g_gsignum == 0);
}
