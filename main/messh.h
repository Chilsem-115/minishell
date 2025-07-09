#ifndef MESSH_H
# define MESSH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenize.h"
# include "libft.h"

/* Token types */
typedef enum	e_tokentype
{
    /* Basic tokens */
    TOK_WORD,

    /* Quoting */
    TOK_SQUOTE,
    TOK_DQUOTE,

    /* Control operators */
    TOK_PIPE,       // |
    TOK_OR,         // ||
    TOK_AND,        // &&

    /* Redirections */
    TOK_REDIR_IN,   // <
    TOK_HEREDOC,    // <<
    TOK_REDIR_OUT,  // >
    TOK_REDIR_APPEND, // >>
	
	/* subshell */
	TOK_LPAREN,     // (
	TOK_RPAREN,     // )

    /* Expansions */
    TOK_ENV_VAR,    // $VAR
    TOK_EXIT_STATUS // $?
}	t_tokentype;

typedef struct	s_data
{
	char		*line;
	t_list		*tokens;
	t_ast_node	*ast;
}	t_data;

void	status_init(t_data *status);
void	status_destroy(t_data *status);

#endif
