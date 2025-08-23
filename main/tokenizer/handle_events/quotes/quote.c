
#include "tokenize.h"

static size_t	advance_word_end(t_tokenizer_state *ctx, char *line, size_t i)
{
	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quoted(ctx, line, i);
		else
			i++;
	}
	return (i);
}

char	*mark_syntactic_quotes(const char *s)
{
	size_t	i;
	size_t	j;
	int		sq;
	int		dq;
	char	*out;

	if (!s)
		return (NULL);
	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	init_state(&i, &j, &sq, &dq);
	while (s[i])
	{
		out[j] = handle_char(s[i], &sq, &dq);
		j++;
		i++;
	}
	out[j] = '\0';
	return (out);
}

int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*word;
	char	*marked;

	if (line[ctx->pos] != '\'' && line[ctx->pos] != '"')
		return (0);
	start = ctx->pos;
	i = ctx->pos;
	i += skip_quoted(ctx, line, i);
	i = advance_word_end(ctx, line, i);
	word = ft_strndup(&line[start], i - start);
	if (!word)
		tokenizer_error(ERR_MEMORY);
	marked = mark_syntactic_quotes(word);
	free(word);
	if (!marked)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, marked, TOK_WORD);
	ctx->pos = i;
	return (1);
}
