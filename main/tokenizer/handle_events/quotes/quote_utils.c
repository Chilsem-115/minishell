
#include "tokenize.h"

int	is_syntactic(int sq, int dq, char c)
{
	if (!dq && c == '\'')
		return (1);
	if (!sq && c == '"')
		return (1);
	return (0);
}

void	toggle_state(int *sq, int *dq, char c)
{
	if (c == '\'')
		*sq = !*sq;
	else if (c == '"')
		*dq = !*dq;
}

char	get_sentinel(char c)
{
	if (c == '\'')
		return (SQ_SENTINEL);
	return (DQ_SENTINEL);
}

void	init_state(size_t *i, size_t *j, int *sq, int *dq)
{
	*i = 0;
	*j = 0;
	*sq = 0;
	*dq = 0;
}

char	handle_char(char c, int *sq, int *dq)
{
	if (is_syntactic(*sq, *dq, c))
	{
		toggle_state(sq, dq, c);
		return (get_sentinel(c));
	}
	return (c);
}
