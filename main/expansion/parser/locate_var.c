/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:37:13 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/27 01:34:34 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

static int	find_char(const char *s, char c, int start)
{
	const char	*found;

	if (!s || start < 0)
		return (-1);
	if ((int)ft_strlen(s) < start)
		return (-1);
	s += start;
	found = ft_strchr(s, c);
	if (!found)
		return (-1);
	return (start + (int)(found - s));
}

static t_emode	var_mode_at(const char *s, int pos)
{
	int	in_sq;
	int	in_dq;
	int	i;

	if (!s || s[pos] != '$')
		return (EXP_NO);
	in_sq = 0;
	in_dq = 0;
	i = 0;
	while (s[i] && i < pos)
	{
		if (!in_dq && (s[i] == '\'' || s[i] == SQ_SENTINEL))
			in_sq = !in_sq;
		else if (!in_sq && (s[i] == '\"' || s[i] == DQ_SENTINEL))
			in_dq = !in_dq;
		i++;
	}
	if (in_sq)
		return (EXP_NO);
	if (in_dq)
		return (EXP_DQ);
	return (EXP_UNQ);
}

int	next_dollar(const char *s, int start, t_emode *out_mode)
{
	int		pos;
	t_emode	mode;

	pos = start;
	while (1)
	{
		pos = find_char(s, '$', pos);
		if (pos == -1)
			break ;
		mode = var_mode_at(s, pos);
		if (mode != EXP_NO)
		{
			if (out_mode)
				*out_mode = mode;
			return (pos);
		}
		pos++;
	}
	return (-1);
}
