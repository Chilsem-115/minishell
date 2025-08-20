/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:34:30 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:35:45 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenize.h"

void	create_token(t_tokenizer_state *ctx, char *text, t_tokentype type)
{
	t_token	*tok;
	t_list	*node;

	tok = malloc(sizeof(t_token));
	if (!tok)
		tokenizer_error(ERR_MEMORY);
	tok->text = text;
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

void	ctx_init(t_tokenizer_state *ctx)
{
	ctx->pos = 0;
	ctx->tokens = NULL;
	ctx->error = ERR_NONE;
}

/* NOTE: this function is unsafe; not recommended with NULL or empty string */
t_list	*tokenize(char *line)
{
	t_tokenizer_state	ctx;

	ctx_init(&ctx);
	while (line[ctx.pos])
	{
		while (ft_isspace(line[ctx.pos]))
			ctx.pos++;
		if (!line[ctx.pos])
			break ;
		if (operator_handler(&ctx, line))
			continue ;
		word_handler(&ctx, line);
	}
	return (ctx.tokens);
}
