
#include "ast.h"
#include "generate.h"
#include "tokenize.h"

t_ast_node	*generate_ast(t_list *tokens, const char *line)
{
	t_ast_node	*root;
	t_token		*tok;

	root = NULL;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == TOK_PIPE)
			root = handle_pipe(root, &tokens, line);
		else if (is_redirection(tok->type))
			root = handle_redir(root, &tokens, line);
		else
			root = handle_cmd(&tokens, line);
	}
	return (root);
}
