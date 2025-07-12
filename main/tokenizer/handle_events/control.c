
#include "tokenize.h"

static int	handle_pipe(t_tokenizer_state *ctx)
{
	return (emit_token(ctx, TOK_PIPE, 1));
}

int	dispatch_control_ops(t_tokenizer_state *ctx, char *line)
{
	char	c;

	c = line[ctx->pos];
	if (c == '|')
		return (handle_pipe(ctx));
	return (0);
}
