/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:22:26 by itamsama          #+#    #+#             */
/*   Updated: 2024/12/22 16:45:09 by itamsama         ###   ########.fr       */
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
		count += write_char(fd ,(n % 10) + '0');
	}
	return (count);
}
