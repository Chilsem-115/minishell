/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:15 by itamsama          #+#    #+#             */
/*   Updated: 2024/12/23 13:30:05 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_ptr(int fd, void *ptr)
{
	int	count;

	count = 0;
	if (ptr == NULL)
		count += write_str(fd, "(nil)");
	else
	{
		count += write_str(fd, "0x");
		count += write_hexa(fd, (unsigned long)ptr, 0); // 0 = lowercase hex
	}
	return (count);
}

