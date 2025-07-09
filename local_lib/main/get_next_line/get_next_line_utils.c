/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:59:34 by itamsama          #+#    #+#             */
/*   Updated: 2025/05/21 00:05:34 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	char	*dst;
	int		len;

	len = 0;
	if (!src || !*src)
		return (NULL);
	while (src[len])
		len++;
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	dst[len] = '\0';
	while (len--)
		dst[len] = src[len];
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	char			*ret;
	int				index;
	int				i;
	int				j;

	index = 0;
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			i++;
	while (s2[j])
		j++;
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (NULL);
	ret = str;
	while (i--)
		*str++ = s1[index++];
	index = 0;
	while (j--)
		*str++ = s2[index++];
	*str++ = '\0';
	return (free(s1), free(s2), ret);
}

int	handle_buffer(char **line, char *tmp, ssize_t read_val, char **remain)
{
	if (read_val > 0)
		return (handle_tmp(remain, tmp, line));
	else if (read_val == 0)
	{
		free(tmp);
		if (!*line)
			*line = NULL;
	}
	else if (read_val == -1)
	{
		free(tmp);
		if (*remain)
			free(*remain);
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
	}
	return (1);
}

int	handle_static(char **remain, char **line)
{
	int		i;
	char	*beg;

	i = 0;
	if (!remain || !*remain)
		return (0);
	while (remain[0][i])
	{
		if (remain[0][i] == '\n')
		{
			beg = *remain;
			*remain = ft_strdup(*remain + i + 1);
			beg[i + 1] = '\0';
			*line = ft_strdup(beg);
			free(beg);
			return (1);
		}
		i++;
	}
	if (**remain)
		*line = ft_strdup(*remain);
	return (free(*remain), *remain = NULL, 0);
}

int	handle_tmp(char **remain, char *tmp, char **line)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			if (!(tmp[i + 1] == '\0'))
			{
				*remain = ft_strdup(tmp + i + 1);
				if (!*remain)
				{
					*line = NULL;
					return (1);
				}
				tmp[i + 1] = '\0';
				*line = ft_strjoin(*line, tmp);
			}
			else
				*line = ft_strjoin(*line, &tmp[0]);
			return (1);
		}
		i++;
	}
	return (0);
}
