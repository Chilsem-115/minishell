/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:36:57 by itamsama          #+#    #+#             */
/*   Updated: 2025/05/21 00:04:06 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;
	char		*tmp;
	ssize_t		read_val;

	line = NULL;
	tmp = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (handle_static(&remain, &line))
		return (line);
	while (1)
	{
		tmp = (char *)malloc((BUFFER_SIZE + 1));
		if (!tmp)
			return (NULL);
		read_val = read(fd, tmp, BUFFER_SIZE);
		if (read_val >= 0)
			tmp[read_val] = '\0';
		if (handle_buffer(&line, tmp, read_val, &remain))
			return (line);
		else
			line = ft_strjoin(line, tmp);
	}
}
