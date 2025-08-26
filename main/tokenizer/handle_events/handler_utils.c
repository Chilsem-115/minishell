
#include "tokenize.h"

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	add_token(t_tokenizer_state *ctx, t_tokentype type, size_t size)
{
	ctx->pos += size;
	create_token(ctx, NULL, type);
	return (1);
}

void	token_free(void *ptr)
{
	t_token	*tok;

	if (!ptr)
		return ;
	tok = (t_token *)ptr;
	ft_free(tok->text);
	ft_free(tok);
}

void	create_token(t_tokenizer_state *ctx, char *text, t_tokentype type)
{
	t_token	*tok;
	t_list	*node;

	tok = garbage_coll(0, sizeof(t_token));
	if (!tok)
		return ;
	tok->text = text;
	tok->type = type;
	tok->expand = 1;
	node = ft_lstnew(tok);
	if (!node)
	{
		ft_free(tok->text);
		ft_free(tok);
		return ;
	}
	ft_lstadd_back(&ctx->tokens, node);
}

size_t	skip_quoted(const char *s, size_t pos)
{
	const char	q = s[pos];
	size_t		i;

	i = pos + 1;
	while (s[i] && s[i] != q)
		i++;
	if (!s[i])
		return (i - pos);
	return (i - pos + 1);
}

