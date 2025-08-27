/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:45:52 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/27 02:10:37 by oessmiri         ###   ########.fr       */
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

/* advances i to the end of
 * the current WORD (handles quotes); returns new index */
static size_t	advance_word(char *line, size_t i)
{
	size_t	cons;

	while (line[i] && !ft_isspace((unsigned char)line[i])
		&& !is_op_char(line[i]))
	{
		if (is_quote_char(line[i]))
		{
			cons = skip_quoted(line, i);
			i += cons;
		}
		else
			i++;
	}
	return (i);
}

/* slices [start,end); only mark syntactic quotes if ctx->mark_quotes == 1 */
static int	create_marked_word(t_tokenizer_state *ctx, char *line,
		size_t start, size_t end)
{
	size_t	len;
	char	*word;
	char	*marked;

	len = end - start;
	word = ft_strndup(&line[start], len);
	if (!word)
		return (0);
	if (ctx->mark_quotes)
	{
		marked = mark_syntactic_quotes(word);
		ft_free(word);
		if (!marked)
			return (0);
		create_token(ctx, marked, TOK_WORD);
	}
	else
		create_token(ctx, word, TOK_WORD);
	return (1);
}

void	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	end;
	size_t	i;

	i = ctx->pos;
	if (!line[i] || ft_isspace((unsigned char)line[i]) || is_op_char(line[i]))
		return ;
	start = i;
	end = advance_word(line, i);
	create_marked_word(ctx, line, start, end);
	ctx->pos = end;
	return ;
}
