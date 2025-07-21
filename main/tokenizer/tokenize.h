/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@studnet.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:37:20 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:39:50 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

/* System headers */
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>
# include "messh.h"
# include "libft.h"

/* Constants */
# define MAX_TOKENS 4096

/* Token types */
typedef enum e_tokentype
{
	TOK_WORD,
	TOK_SQUOTE,
	TOK_DQUOTE,
	TOK_PIPE,
	TOK_EXIT_STATUS,
	TOK_REDIR_IN,
	TOK_HEREDOC,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_ENV_VAR
}	t_tokentype;

/* Error codes */
typedef enum e_tok_err
{
	ERR_NONE,
	ERR_UNCLOSED_QUOTE,
	ERR_EMPTY_INPUT,
	ERR_MEMORY,
	ERR_ESCAPE_SEQ,
}	t_tok_err;

/* Token structure */
typedef struct s_token
{
	char		*text;
	t_tokentype	type;
}	t_token;

/* Tokenizer state */
typedef struct s_tokenizer_state
{
	size_t		pos;
	t_list		*tokens;
	t_tok_err	error;
}	t_tokenizer_state;

/* ======================= */
/*      CORE FUNCTIONS     */
/* ======================= */

t_list	*tokenize(char *line);
void	tokenizer_error(t_tok_err err);

/* ======================= */
/*    STATE MANAGEMENT     */
/* ======================= */

void	ctx_init(t_tokenizer_state *ctx);

/* ======================= */
/*      TOKEN HANDLERS     */
/* ======================= */

/* Quote handling */
int		quote_handler(t_tokenizer_state *ctx, char *line);
int		handle_quote(t_tokenizer_state *ctx, char *line);

/* Operator handling */
int		operator_handler(t_tokenizer_state *ctx, char *line);
int		dispatch_control_ops(t_tokenizer_state *ctx, char *line);
int		dispatch_redirections(t_tokenizer_state *ctx, char *line);
int		add_token(t_tokenizer_state *ctx, t_tokentype type, size_t size);

/* Word handling */
int		word_handler(t_tokenizer_state *ctx, char *line);

/* ENV handling */
void	handle_exit_status(t_tokenizer_state *ctx, char *line);
void	handle_env_variable(t_tokenizer_state *ctx, char *line);
void	handle_dollar_literal(t_tokenizer_state *ctx);
int		env_handler(t_tokenizer_state *ctx, char *line);

void	create_token(t_tokenizer_state *ctx, char *text, t_tokentype type);

#endif
