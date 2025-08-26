/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:12:21 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 00:02:17 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(const char *s, int fd)
{
	size_t	len;
	char	*buf;

	len = ft_strlen(s);
	buf = garbage_coll(0, len + 2);
	if (!buf)
		return ;
	ft_memcpy(buf, s, len);
	buf[len] = '\n';
	buf[len + 1] = '\0';
	write(fd, buf, len +1);
	ft_free(buf);
}
