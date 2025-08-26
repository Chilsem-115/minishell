/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:47:04 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 08:33:34 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote_char(char c)
{
	if (c == '\'' || c == '"' || c == SQ_SENTINEL || c == DQ_SENTINEL)
		return (1);
	return (0);
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

int	add_token(t_tokenizer_state *ctx, t_tokentype type, size_t size)
{
	ctx->pos += size;
	create_token(ctx, NULL, type);
	return (1);
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
