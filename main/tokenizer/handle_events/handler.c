
#include "tokenize.h"

int	add_token(t_tokenizer_state *ctx, t_tokentype type, size_t size)
{
	ctx->pos += size;
	create_token(ctx, NULL, type);
	return (1);
}

int	env_handler(t_tokenizer_state *ctx, char *line)
{
	if (line[ctx->pos] != '$')
		return (0);
	if (line[ctx->pos + 1] == '?')
		handle_exit_status(ctx, line);
	else if (isalpha(line[ctx->pos + 1]) || line[ctx->pos + 1] == '_')
		handle_env_variable(ctx, line);
	else
		handle_dollar_literal(ctx);
	return (1);
}

int	operator_handler(t_tokenizer_state *ctx, char *line)
{
	if (dispatch_redirections(ctx, line))
		return (1);
	if (dispatch_control_ops(ctx, line))
		return (1);
	return (0);
}

int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	if (line[ctx->pos] == '\'' || line[ctx->pos] == '"')
		return (handle_quote(ctx, line));
	return (0);
}

int	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	char	*word;

	start = ctx->pos;
	while (line[ctx->pos]
		&& !isspace((unsigned char)line[ctx->pos])
		&& line[ctx->pos] != '|'
		&& line[ctx->pos] != '<'
		&& line[ctx->pos] != '>'
		&& line[ctx->pos] != '"'
		&& line[ctx->pos] != '\''
		&& line[ctx->pos] != '$')
		ctx->pos++;
	if (ctx->pos == start)
		return (0);
	word = ft_strndup(&line[start], ctx->pos - start);
	if (!word)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, word, TOK_WORD);
	return (1);
}
