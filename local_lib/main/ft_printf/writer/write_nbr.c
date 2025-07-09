/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:51:58 by itamsama          #+#    #+#             */
/*   Updated: 2024/12/22 16:45:12 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_nbr(int fd, int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += write_char(fd, '-');
		count += write_char(fd, '2');
		n = 147483648;
	}
	if (n < 0)
	{
		count += write_char(fd, '-');
		n = -n;
	}
	if (n < 10)
		count += write_char(fd, n + '0');
	else
	{
		count += write_nbr(fd ,n / 10);
		count += write_char(fd ,(n % 10) + '0');
	}
	return (count);
}
