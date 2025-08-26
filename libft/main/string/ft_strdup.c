/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:53:53 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 05:07:44 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	i;

	if (!src)
		return (NULL);
	i = ft_strlen(src) + 1;
	dst = (char *)garbage_coll(0, i);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, i);
	return (dst);
}
