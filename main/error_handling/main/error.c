/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 03:28:48 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/27 04:29:54 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include <stdio.h>
#include <stdlib.h>

static t_error g_errors[MAX_ERRORS];
static size_t g_error_count = 0;

void	register_error(t_error_code code, const char *msg, void (*handler)(void *))
{
	if (g_error_count >= MAX_ERRORS)
		return ;
	g_errors[g_error_count++] = (t_error){code, msg, handler};
}

void	report_error(t_error_code code, void *context)
{
	for (size_t i = 0; i < g_error_count; ++i)
	{
		if (g_errors[i].code == code)
		{
			fprintf(stderr, "Error [%d]: %s\n", code, g_errors[i].message);
			if (g_errors[i].handler)
				g_errors[i].handler(context);
			return ;
		}
	}
	ft_dprintf(2, "Unknown error code: %d\n", code);
}
