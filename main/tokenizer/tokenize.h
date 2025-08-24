/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@studnet.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:37:20 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/24 15:43:56 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

/* System headers */
# include "libft.h"
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* Constants */
# define SQ_SENTINEL '\x01'
# define DQ_SENTINEL '\x02'

/* Token types */
typedef enum e_tokentype
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_HEREDOC,
	TOK_DELIM,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_EXIT_STATUS
}	t_tokentype;

// Error codes 
typedef enum e_tok_err
{
	ERR_NONE,
	ERR_EMPTY_INPUT,
	ERR_MEMORY,
	ERR_ESCAPE_SEQ,
	ERR_UNCLOSED_QUOTE
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
	//t_tok_err	error;
	int			mark_quotes;
}	t_tokenizer_state;


/* ======================= */
/*      CORE FUNCTIONS     */
/* ======================= */

t_list	*tokenize(char *line);
t_list	*tokenize_nomark(char *line);

/* ======================= */
/*      TOKEN HANDLERS     */
/* ======================= */

/* Operator handling (return 1 if consumed, 0 otherwise) */
int		operator_handler(t_tokenizer_state *ctx, char *line);
int		dispatch_control_ops(t_tokenizer_state *ctx, char *line);
int		dispatch_redirections(t_tokenizer_state *ctx, char *line);

/* Word handling (return 1 if consumed, 0 otherwise) */
int		word_handler(t_tokenizer_state *ctx, char *line);
int		quote_handler(t_tokenizer_state *ctx, char *line);

/* ======================= */
/*     HANDLER UTILITIES   */
/* ======================= */

int		is_op_char(char c);
int		add_token(t_tokenizer_state *ctx, t_tokentype type, size_t size);
void	token_free(void *ptr);
void	create_token(t_tokenizer_state *ctx, char *text, t_tokentype type);
size_t	skip_quoted(/*t_tokenizer_state *ctx,*/ const char *s, size_t pos);

/* quote handling utils */
int		is_syntactic(int sq, int dq, char c);
void	toggle_state(int *sq, int *dq, char c);
void	init_state(size_t *i, size_t *j, int *sq, int *dq);
char	handle_char(char c, int *sq, int *dq);
char	get_sentinel(char c);
int		is_quote_char(char c);

/* Mark only syntactic quotes in a freshly formed WORD */
char	*mark_syntactic_quotes(const char *s);

/* Error handling*/
void	err_unclosed_quote(void);
int		validate_quotes_line(const char *s);
int		validate_redirs(t_list *lst);
int		validate_pipes(t_list *tokens);

void	err_unexpected_token(const char *tok);
const char	*find_redir_error_token(t_list *lst);
const char	*find_pipe_error_token(t_list *tokens);

#endif
