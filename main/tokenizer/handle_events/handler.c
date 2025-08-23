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

/*
int	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	char	*word;

	start = ctx->pos;
	while (line[ctx->pos] && !isspace((unsigned char)line[ctx->pos])
		&& line[ctx->pos] != '|' && line[ctx->pos] != '<'
		&& line[ctx->pos] != '>')
		ctx->pos++;
	if (ctx->pos == start)
		return (0);
	word = ft_strndup(&line[start], ctx->pos - start);
	if (!word)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, word, TOK_WORD);
	return (1);
}
*/

int	operator_handler(t_tokenizer_state *ctx, char *line)
{
	if (dispatch_redirections(ctx, line))
		return (1);
	if (dispatch_control_ops(ctx, line))
		return (1);
	return (0);
}


int	word_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*word;

	i = ctx->pos;
	if (!line[i] || isspace((unsigned char)line[i]) || is_op_char(line[i]))
		return (0);
	start = i;
	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			size_t	cons = skip_quoted(ctx, line, i);
			i += cons;
			continue ;
		}
		i++;
	}
	word = ft_strndup(&line[start], i - start);
	if (!word)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, word, TOK_WORD);
	ctx->pos = i;
	return (1);
}
