/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:02:49 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/22 18:29:17 by oessmiri         ###   ########.fr       */
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

bool	heredoc(char **list)
{
	int		fd_hd;
	char	*s;
	char	*file;

	fd_hd = name_file(&file);
	g_gsignum = 0;
	while (1)
	{
		if (g_gsignum != 0)
			return (false);
		g_gsignum = 0;
		s = readline("> ");
		if (s && ft_strncmp(s, *list, ft_strlen(s) + 1) != 0)
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
	*list = file;
	return (true);
}
