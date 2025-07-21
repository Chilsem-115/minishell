/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:40:34 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:40:55 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include "libft.h"
#include "tokenize.h"

void	handle_exit_status(t_tokenizer_state *ctx, char *line)
{
	char	*text;

	text = ft_strndup(&line[ctx->pos], 2);
	if (!text)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, text, TOK_EXIT_STATUS);
	ctx->pos += 2;
}

void	handle_env_variable(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*text;

	start = ctx->pos;
	i = start + 1;
	while (isalnum(line[i]) || line[i] == '_')
		i++;
	text = ft_strndup(&line[start], i - start);
	if (!text)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, text, TOK_ENV_VAR);
	ctx->pos = i;
}

void	handle_dollar_literal(t_tokenizer_state *ctx)
{
	char	*text;

	text = ft_strndup("$", 1);
	if (!text)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, text, TOK_WORD);
	ctx->pos++;
}
