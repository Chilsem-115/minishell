
#include "tokenize.h"

int	is_quote_char(char c)
{
	if (c == '\'' || c == '"' || c == SQ_SENTINEL || c == DQ_SENTINEL)
		return (1);
	return (0);
}

/* s[pos] is a quote/sentinel; skip to its matching closer or same sentinel */
size_t	skip_quoted_any(t_tokenizer_state *ctx, const char *s, size_t pos)
{
	size_t	i;
	char	open;
	char	close;

	i = pos + 1;
	open = s[pos];
	close = open;
	if (open == SQ_SENTINEL)
		close = '\'';
	else if (open == DQ_SENTINEL)
		close = '"';
	while (s[i] && s[i] != close && s[i] != open)
		i++;
	if (!s[i])
		ctx->error = ERR_ESCAPE_SEQ;
	if (s[i])
		i++;
	return (i - pos);
}
