
#include "tokenize.h"

void	handle_quote(t_tokenizer_state *ctx, char *line, char quote)
{
    int	start;

	start = ctx->pos;
	ctx->pos++;
	while (line[ctx->pos] && line[ctx->pos] != quote)
		ctx->pos++;
	if (line[ctx->pos] == quote)
	{
		ctx->current.start = start;
		ctx->current.length = (ctx->pos - start) + 1;
		create_token(ctx);
		ctx->pos++;
	}
	else
	{
		ctx->current.start = start;
		ctx->current.length = strlen(line) - start;
		create_token(ctx);
		tokenizer_error(ERR_UNCLOSED_QUOTE);
	}
}
