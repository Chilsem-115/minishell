
#include "tokenize.h"
#include "libft.h"

void	create_token(t_tokenizer_state *ctx, const char *text, t_tokentype type)
{
	t_token	*tok = malloc(sizeof(t_token));
	t_list	*node;

	if (!tok)
		tokenizer_error(ERR_MEMORY);

	tok->text = ft_strdup(text);
	if (!tok->text)
	{
		free(tok);
		tokenizer_error(ERR_MEMORY);
	}
	tok->type = type;

	node = ft_lstnew(tok);
	if (!node)
	{
		free(tok->text);
		free(tok);
		tokenizer_error(ERR_MEMORY);
	}
	ft_lstadd_back(&ctx->tokens, node);
}

void ctx_init(t_tokenizer_state *ctx)
{
	ctx->pos    = 0;
	ctx->tokens = NULL;
	ctx->error  = ERR_NONE;
}

/* NOTE: this function is unsafe; not recommended with NULL or empty string */
t_list	*tokenize(char *line)
{
	t_tokenizer_state ctx;

	ctx_init(&ctx);
	while (line[ctx.pos])
	{
		while (ft_isspace(line[ctx.pos]))
			ctx.pos++;
		if (!line[ctx.pos])
			break ;
		if (quote_handler(&ctx, line) || operator_handler(&ctx, line) ||
			env_handler(&ctx, line))
			continue;
		word_handler(&ctx, line);
	}
	return (ctx.tokens);
}
