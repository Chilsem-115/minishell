/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:44:04 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:44:18 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "tokenize.h"

void	err_unclosed_quote(void)
{
	const char	*msg;

	msg = "minishell: syntax error unclosed quote\n";
	write(2, msg, ft_strlen(msg));
}

void	err_unexpected_token(const char *tok)
{
	const char	*pre;
	const char	*post;

	pre = "minishell: syntax error near unexpected token `";
	post = "'\n";
	if (!tok || *tok == '\0')
		tok = "newline";
	write(2, pre, ft_strlen(pre));
	write(2, tok, ft_strlen(tok));
	write(2, post, ft_strlen(post));
}
