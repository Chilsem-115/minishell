
#include "tokenize.h"

static int	handle_or(t_tokenizer_state *ctx)
{
	return (emit_token(ctx, TOK_OR, 2));
}

static int	handle_and(t_tokenizer_state *ctx)
{
	return (emit_token(ctx, TOK_AND, 2));
}

static int	handle_pipe(t_tokenizer_state *ctx)
{
	return (emit_token(ctx, TOK_PIPE, 1));
}

static int	handle_parenthesis(t_tokenizer_state *ctx, char *line)
{
	char	c;

	c = line[ctx->pos];
	if (c == '(')
		return (emit_token(ctx, TOK_LPAREN, 1));
	else if (c == ')')
		return (emit_token(ctx, TOK_RPAREN, 1));
	return (0);
}

int	dispatch_control_ops(t_tokenizer_state *ctx, char *line)
{
	char	c;
	char	n;

	c = line[ctx->pos];
	n = line[ctx->pos + 1];
	if (c == '|' && n == '|')
		return (handle_or(ctx));
	else if (c == '&' && n == '&')
		return (handle_and(ctx));
	else if (c == '|')
		return (handle_pipe(ctx));
	else if (c == '(' || c == ')')
		return (handle_parenthesis(ctx, line));
	return (0);
}
