/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:18:22 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 20:36:01 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hexa(int fd, unsigned long num, int uppercase)
{
	char	*hex_digits;
	int		len;

	len = 0;
	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (num >= 16)
		len += hexa(fd, num / 16, uppercase);
	len += write_char(fd, hex_digits[num % 16]);
	return (len);
}

int	write_hexa(int fd, unsigned long num, int uppercase)
{
	if (num == 0)
		return (write_char(fd, '0'));
	return (hexa(fd, num, uppercase));
}
