
#include "tokenize.h"

/* advance until whitespace/op, skipping over balanced quotes */
static size_t	advance_word_end(char *line, size_t i)
{
	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quoted(line, i);
		else
			i++;
	}
	return (i);
}

/* copy [src, src+len) while removing syntactic quotes */
static char	*unquote_copy(const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	int		in_sq;
	int		in_dq;
	char	*out;

	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	while (i < len)
	{
		if (!in_dq && src[i] == '\'')
			in_sq = !in_sq;
		else if (!in_sq && src[i] == '"')
			in_dq = !in_dq;
		else if (!in_sq && src[i] == '\\' && (i + 1) < len)
			out[j++] = src[++i];
		else
			out[j++] = src[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

/* handle a word that begins with ' or " */
int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*raw;
	char	*text;

	if (line[ctx->pos] != '\'' && line[ctx->pos] != '"')
		return (0);
	start = ctx->pos;
	i = ctx->pos;
	i += skip_quoted(line, i);
	i = advance_word_end(line, i);
	raw = ft_strndup(&line[start], i - start);
	if (!raw)
		return (0);
	text = unquote_copy(raw, i - start);
	free(raw);
	if (!text)
		return (0);
	create_token(ctx, text, TOK_WORD);
	ctx->pos = i;
	return (1);
}

