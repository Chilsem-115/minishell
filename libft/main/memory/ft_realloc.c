/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:39:10 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 00:01:47 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new_ptr = garbage_coll(0, new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr && old_size > 0)
		ft_memcpy(new_ptr, ptr, old_size);
	ft_free(ptr);
	return (new_ptr);
}
