/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:42:49 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:43:07 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

static const char	*g_error_messages[] = {
	"No error",						// ERR_NONE
	"Unclosed quote",				// ERR_UNCLOSED_QUOTE
	"Unclosed group",				// ERR_UNCLOSED_GROUP
	"Empty input",					// ERR_EMPTY_INPUT
	"Too many tokens",				// ERR_OVERFLOW
	"Memory allocation failed",		// ERR_MEMORY
	"Invalid escape sequence",		// ERR_ESCAPE_SEQ
	"Syntax error"					// ERR_SYNTAX
};

void	tokenizer_error(t_tok_err err)
{
	if (err == ERR_NONE)
		exit(0);
	else if (err >= 0 && err < (int)(sizeof(g_error_messages) / sizeof(char *)))
		fprintf(stderr, "Tokenizer error: %s\n", g_error_messages[err]);
	else
		fprintf(stderr, "Tokenizer error: Unknown error code (%d)\n", err);
	exit(EXIT_FAILURE);
}
