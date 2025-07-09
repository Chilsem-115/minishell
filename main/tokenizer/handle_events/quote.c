
#include "tokenize.h"

/*
void handle_quote(t_tokenizer_state *ctx, char *line, char quote)
{
    int start = ctx->pos;
    ctx->pos++;  // Skip opening quote

    // Scan until closing quote
    while (line[ctx->pos] && line[ctx->pos] != quote) {
        ctx->pos++;
    }

    if (line[ctx->pos] == quote) {
        // Complete quoted token
        ctx->current.start = start;
        ctx->current.length = (ctx->pos - start) + 1;
        create_token(ctx, line);
        ctx->pos++;
    } else {
        // Unclosed quote error
        ctx->current.start = start;
        ctx->current.length = strlen(line) - start;
        create_token(ctx, line);
        tokenizer_error(ERR_UNCLOSED_QUOTE);
    }
}
*/

void handle_quote(t_tokenizer_state *ctx, char *line, char quote)
{
	ctx->current.start = ctx->pos;
	ctx->pos++;
	while (line[ctx->pos] && line[ctx->pos] != quote)
		ctx->pos++;
	if (line[ctx->pos] == quote)
	{
		ctx->pos++;
		ctx->current.length = ctx->pos - ctx->current.start;

		if (quote == '\'')
			ctx->current.type = TOK_SQUOTE;
		else if (quote == '"')
			ctx->current.type = TOK_DQUOTE;
		create_token(ctx);
	}
	else
	{
		ctx->current.length = ctx->pos - ctx->current.start;
		if (quote == '\'')
			ctx->current.type = TOK_SQUOTE;
		else if (quote == '"')
			ctx->current.type = TOK_DQUOTE;
		create_token(ctx);
		tokenizer_error(ERR_UNCLOSED_QUOTE);
	}
}
