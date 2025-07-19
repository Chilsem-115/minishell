
#include "tokenize.h"

static int	handle_pipe(t_tokenizer_state *ctx)
{
	return (add_token(ctx, TOK_PIPE, 1));
}

int	dispatch_control_ops(t_tokenizer_state *ctx, char *line)
{
	if (line[ctx->pos] == '|')
		return (handle_pipe(ctx));
	return (0);
}
