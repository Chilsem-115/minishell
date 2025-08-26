/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_name.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:26:49 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/26 00:03:22 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"

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
	char			random_part[9];
	unsigned char	byte;
	char			*filename;
	const char		charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY\
	Z0123456789";

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
		ft_free(name);
		return (NULL);
	}
	ft_strcpy(full_path, "/tmp/");
	ft_strcat(full_path, name);
	ft_free(name);
	return (full_path);
}
