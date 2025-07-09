
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

/* Error codes */
typedef enum e_tok_err
{
    ERR_NONE,           // No error
    ERR_UNCLOSED_QUOTE, // Unterminated quote
    ERR_UNCLOSED_GROUP, // Unterminated group
    ERR_EMPTY_INPUT,    // Input is empty
    ERR_OVERFLOW,       // Too many tokens
    ERR_MEMORY,         // Allocation failure
    ERR_ESCAPE_SEQ,     // Invalid escape sequence
    ERR_SYNTAX          // General syntax error
} t_tok_err;

/* Token structure */
typedef struct s_token
{
    size_t      start;
    size_t      length;
    t_tokentype type;
} t_token;

/* Tokenizer state */
typedef struct s_tokenizer_state
{
    t_token     current;
    size_t      pos;
	t_list		*tokens;
    t_tok_err   error;
} t_tokenizer_state;

/* ======================= */
/*      CORE FUNCTIONS     */
/* ======================= */

t_list             	*tokenize(char *line);
void                tokenizer_error(t_tok_err err);

/* ======================= */
/*    STATE MANAGEMENT     */
/* ======================= */

void                ctx_init(t_tokenizer_state *ctx);
void                create_token(t_tokenizer_state *ctx);

/* ======================= */
/*      TOKEN HANDLERS     */
/* ======================= */

/* Quote handling */
int                 quote_handler(t_tokenizer_state *ctx, char *line);
void                handle_quote(t_tokenizer_state *ctx, char *line, char quote);

/* Operator handling */
int		operator_handler(t_tokenizer_state *ctx, char *line);
int		dispatch_control_ops(t_tokenizer_state *ctx, char *line);
int		dispatch_redirections(t_tokenizer_state *ctx, char *line);

/* Word handling */
int                 word_handler(t_tokenizer_state *ctx, char *line);

int	emit_token(t_tokenizer_state *ctx, t_tokentype type, int length);
int	env_handler(t_tokenizer_state *ctx, char *line);

#endif
