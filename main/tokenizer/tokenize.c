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


static void	ctx_init(t_tokenizer_state *ctx)
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
		if (operator_handler(&ctx, line) || quote_handler(&ctx, line))
			continue ;
		word_handler(&ctx, line);
	}
	return (ctx.tokens);
}
