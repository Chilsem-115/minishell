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

static size_t	advance_word(char *line, size_t i)
{
	size_t	cons;

	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
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

static char	*unquote_copy(const char *src, size_t len)
{
	size_t	i;
	size_t	j;
	int		in_sq;
	int		in_dq;
	char	*out;

	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	while (i < len)
	{
		if (!in_dq && src[i] == '\'')
			in_sq = !in_sq;
		else if (!in_sq && src[i] == '"')
			in_dq = !in_dq;
		else if (!in_sq && src[i] == '\\' && (i + 1) < len)
			out[j++] = src[++i];
		else
			out[j++] = src[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

static int	create_word(t_tokenizer_state *ctx, char *line,
						size_t start, size_t end)
{
	char	*raw;
	char	*text;

	raw = ft_strndup(&line[start], end - start);
	if (!raw)
		return (0);
	text = unquote_copy(raw, end - start);
	free(raw);
	if (!text)
		return (0);
	create_token(ctx, text, TOK_WORD);
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
	end = advance_word(line, i);
	if (!create_word(ctx, line, start, end))
		return (0);
	ctx->pos = end;
	return (1);
}
