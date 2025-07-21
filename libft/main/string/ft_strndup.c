/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:41:00 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 20:41:27 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dst;

	dst = (char *)malloc(n + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}
