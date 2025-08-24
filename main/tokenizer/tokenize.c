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

/* context data initializer */
static void	ctx_init(t_tokenizer_state *ctx)
{
	ctx->pos = 0;
	ctx->tokens = NULL;
}

/* the main implemenation for tokenizing */
static t_list	*tokenize_impl(char *line)
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
		/*
		if (quote_handler(&ctx, line))
				continue ;
				*/
		word_handler(&ctx, line);
	}
	return (ctx.tokens);
}

/* first pass from the shell: mark quotes -> sentinels */
t_list	*tokenize(char *line)
{
	t_list		*tokens;
	const char	*bad;

	if (!validate_quotes_line(line))
	{
		err_unclosed_quote();
		return (NULL);
	}
	tokens = tokenize_impl(line);
	if (!tokens)
		return (NULL);
	if (!validate_redirs(tokens))
	{
		bad = find_redir_error_token(tokens);
		err_unexpected_token(bad);
		return (NULL);
	}
	if (!validate_pipes(tokens))
	{
		bad = find_pipe_error_token(tokens);
		err_unexpected_token(bad);
		return (NULL);
	}
	return (tokens);
}
