/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deldup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 05:06:46 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 05:07:02 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*deldup(char *str)
{
	char	buf[256];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		while (k < j && buf[k] != str[i])
			k++;
		if (k == j)
			buf[j++] = str[i];
		i++;
	}
	buf[j] = '\0';
	ft_free(str);
	return (ft_strdup(buf));
}
