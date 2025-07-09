/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:27:49 by itamsama          #+#    #+#             */
/*   Updated: 2024/11/15 08:05:43 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_digits(int n, char *temp)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		temp[i++] = (n % 10) + '0';
		n /= 10;
	}
	return (i);
}

static void	reverse_and_copy(char *buffer, char *temp, int len, int is_negative)
{
	int	i;

	i = 0;
	if (is_negative)
		buffer[i++] = '-';
	while (len > 0)
		buffer[i++] = temp[--len];
	buffer[i] = '\0';
}

static void	ft_itoa_stack(int n, char *buffer)
{
	char	temp[12];
	int		len;
	int		is_negative;

	if (n == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return ;
	}
	if (n == -2147483648)
	{
		ft_strcpy(buffer, "-2147483648");
		return ;
	}
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}
	len = fill_digits(n, temp);
	reverse_and_copy(buffer, temp, len, is_negative);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[12];

	ft_itoa_stack(n, buffer);
	write(fd, buffer, ft_strlen(buffer));
}
