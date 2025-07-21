/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:22:26 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 20:37:37 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_unsigned(int fd, unsigned int n)
{
	int	count;

	count = 0;
	if (n < 10)
		count += write_char(fd, n + '0');
	else
	{
		count += write_unsigned(fd, n / 10);
		count += write_char(fd, (n % 10) + '0');
	}
	return (count);
}
