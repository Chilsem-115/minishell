
#include "ast.h"
#include "generate.h"
#include "tokenize.h"

/*
** Entry point: build an AST from a valid token list
*/
t_ast_node	*generate_ast(t_list *tokens)
{
	t_ast_node	*current;

	if (!tokens)
		return (NULL);
	current = consume_command(&tokens);
	if (!current)
		return (NULL);
	current = consume_redirections(&tokens, current);
	if (tokens && is_control(((t_token *)tokens->content)->type))
		current = consume_control(&tokens, current);
	return (make_root(current));
}
