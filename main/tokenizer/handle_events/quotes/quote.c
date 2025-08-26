/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:47:41 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:49:11 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "execute.h"

char	*mark_syntactic_quotes(const char *s)
{
	size_t	i;
	size_t	j;
	int		sq;
	int		dq;
	char	*out;

	if (!s)
		return (NULL);
	out = garbage_coll(0, ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	init_state(&i, &j, &sq, &dq);
	while (s[i])
	{
		out[j] = handle_char(s[i], &sq, &dq);
		j++;
		i++;
	}
	out[j] = '\0';
	return (out);
}

static size_t	advance_word_end(char *line, size_t i)
{
	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
			i += skip_quoted(line, i);
		else
			i++;
	}
	return (i);
}

static char	*dup_and_mark(const char *src, size_t len)
{
	char	*word;
	char	*marked;

	word = ft_strndup(src, len);
	if (!word)
		return (NULL);
	marked = mark_syntactic_quotes(word);
	ft_free(word);
	return (marked);
}

int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*marked;

	if (!ctx->mark_quotes)
		return (0);
	if (line[ctx->pos] != '\'' && line[ctx->pos] != '"')
		return (0);
	start = ctx->pos;
	i = ctx->pos;
	i += skip_quoted(line, i);
	i = advance_word_end(line, i);
	marked = dup_and_mark(&line[start], i - start);
	if (!marked)
	{
		err_unexpected_token("malloc");
		return (0);
	}
	create_token(ctx, marked, TOK_WORD);
	ctx->pos = i;
	return (1);
}
