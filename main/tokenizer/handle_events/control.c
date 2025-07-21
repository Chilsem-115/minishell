/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:40:12 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:40:29 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static int	handle_pipe(t_tokenizer_state *ctx)
{
	return (add_token(ctx, TOK_PIPE, 1));
}

int	dispatch_control_ops(t_tokenizer_state *ctx, char *line)
{
	if (line[ctx->pos] == '|')
		return (handle_pipe(ctx));
	return (0);
}
