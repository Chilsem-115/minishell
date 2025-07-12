
#include "tokenize.h"

int emit_token(t_tokenizer_state *ctx,
               t_tokentype type,
               int length)
{
	ctx->current.type   = type;
	ctx->current.start  = ctx->pos;
	ctx->current.length = length;
	ctx->pos           += length;
	create_token(ctx);
	return (1);
}
/*
int	env_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;

	if (line[ctx->pos] != '$')
		return (0);
	start = ctx->pos;
	ctx->pos++;
	if (line[ctx->pos] == '?')
	{
		ctx->pos++;
		return (emit_token(ctx, TOK_EXIT_STATUS, 2));
	}
	else if (!isalpha(line[ctx->pos + 1]) && line[ctx->pos + 1] != '_')
		return (0);
	i = ctx->pos + 1;
	while (isalnum(line[i]) || line[i] == '_')
		i++;
	return (emit_token(ctx, TOK_ENV_VAR, i - start));
}
*/

int	env_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;

	if (line[ctx->pos] != '$')
		return (0);
	start = ctx->pos;
	ctx->pos++;
	if (line[ctx->pos] == '?')
	{
		ctx->pos++;
		return (emit_token(ctx, TOK_EXIT_STATUS, 2));
	}
	if (!isalpha(line[ctx->pos]) && line[ctx->pos] != '_') {
		ctx->current.type   = TOK_WORD;
		ctx->current.start  = start;
		ctx->current.length = 1;
		create_token(ctx);
		return (1);
	}
	i = ctx->pos;
	while (isalnum(line[i]) || line[i] == '_')
		i++;
	return (emit_token(ctx, TOK_ENV_VAR, i - start));
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
	char	c;

	c = line[ctx->pos];
	if (c == '\'')
	{
		ctx->current.type = TOK_SQUOTE;
		handle_quote(ctx, line, c);
		return (1);
	}
	else if (c == '"')
	{
		ctx->current.type = TOK_DQUOTE;
		handle_quote(ctx, line, c);
		return (1);
	}
	return (0);
}

int	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;

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
	ctx->current.type   = TOK_WORD;
	ctx->current.start  = start;
	ctx->current.length = ctx->pos - start;
	create_token(ctx);
	return (1);
}
