/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:41:27 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:42:04 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "libft.h"

static char	get_quote_type(t_tokenizer_state *ctx, char *line)
{
	char	quote;

	quote = line[ctx->pos];
	ctx->pos++;
	return (quote);
}

static char	*extract_quoted_text(t_tokenizer_state *ctx, char *line, char quote)
{
	size_t	start;
	char	*text;

	start = ctx->pos;
	while (line[ctx->pos] && line[ctx->pos] != quote)
		ctx->pos++;
	if (!line[ctx->pos])
		tokenizer_error(ERR_UNCLOSED_QUOTE);
	text = ft_strndup(&line[start], ctx->pos - start);
	if (!text)
		tokenizer_error(ERR_MEMORY);
	ctx->pos++;
	return (text);
}

static t_tokentype	convert_quote_to_type(char quote)
{
	if (quote == '"')
		return (TOK_DQUOTE);
	return (TOK_SQUOTE);
}

int	handle_quote(t_tokenizer_state *ctx, char *line)
{
	char		quote;
	char		*text;
	t_tokentype	type;

	quote = get_quote_type(ctx, line);
	text = extract_quoted_text(ctx, line, quote);
	type = convert_quote_to_type(quote);
	create_token(ctx, text, type);
	return (1);
}
