
#include <stdlib.h>
#include <string.h>
#include "expansion.h"

static int	find_char(const char *s, char c, int start)
{
	const char	*found;

	if (!s || start < 0)
		return (-1);
	s += start;
	found = strchr(s, c);//?
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
		if (!in_dq && s[i] == '\'')
			in_sq = !in_sq;
		else if (!in_sq && s[i] == '\"')
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

