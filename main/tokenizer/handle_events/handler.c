/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:41:06 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:41:20 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	operator_handler(t_tokenizer_state *ctx, char *line)
{
	if (dispatch_redirections(ctx, line))
		return (1);
	if (dispatch_control_ops(ctx, line))
		return (1);
	return (0);
}

/* advances i to the end of the current WORD (handles quotes); returns new index */
static size_t	advance_word(t_tokenizer_state *ctx, char *line, size_t i)
{
	size_t	cons;

	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (is_quote_char(line[i]))
		{
			cons = skip_quoted(ctx, line, i);
			i += cons;
		}
		else
			i++;
	}
	return (i);
}

/* slices [start,end); only mark syntactic quotes if ctx->mark_quotes == 1 */
static int	create_marked_word(t_tokenizer_state *ctx, char *line, size_t start, size_t end)
{
	size_t	len;
	char	*word;
	char	*marked;

	len = end - start;
	word = ft_strndup(&line[start], len);
	if (!word)
		return (0);
		//tokenizer_error(ERR_MEMORY);
	if (ctx->mark_quotes)
	{
		marked = mark_syntactic_quotes(word);
		free(word);
		if (!marked)
			return (0);
			//tokenizer_error(ERR_MEMORY);
		create_token(ctx, marked, TOK_WORD);
	}
	else
		create_token(ctx, word, TOK_WORD);
	return (1);
}

int	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = ctx->pos;
	if (!line[i] || isspace((unsigned char)line[i]) || is_op_char(line[i]))
		return (0);
	start = i;
	end = advance_word(ctx, line, i);
	create_marked_word(ctx, line, start, end);
	ctx->pos = end;
	return (1);
}
