
#include "ast.h"
#include "tokenize.h"
#include "libft.h"
#include <stdlib.h>

t_ast_node	*make_ctrl(t_list **tokens)
{
	t_token		*tok;
	t_ast_node	*node;
	t_ctrl_op	op;

	if (!tokens || !*tokens)
		return (NULL);
	tok = (*tokens)->content;
	op = map_ctrl_type(tok->type);
	if (op == -1)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = AST_CONTROL;
	node->data.ctrl.op = op;
	node->data.ctrl.left = NULL;
	node->data.ctrl.right = NULL;
	*tokens = (*tokens)->next;
	return (node);
}

t_ast_node	*make_cmd(t_list **tokens)
{
	t_ast_node	*node;
	t_token		*tok;

	if (!tokens || !*tokens)
		return (NULL);
	tok = (*tokens)->content;
	if (tok->type != TOK_WORD)
		return (NULL);
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = AST_COMMAND;
	node->data.cmd.name = ft_strdup(tok->text);
	*tokens = (*tokens)->next;
	node->data.cmd.flags = extract_flags(tokens);
	node->data.cmd.args = extract_args(tokens);
	return (node);
}

t_ast_node	*make_redir(t_list **tokens)
{
	t_ast_node		*node;
	t_token			*tok;
	t_token			*file_tok;
	t_redir_type	redir;

	if (!tokens || !*tokens || !(*tokens)->next)
		return (NULL);
	tok = (*tokens)->content;
	redir = map_redir_type(tok->type);
	if (redir == -1)
		return (NULL);
	*tokens = (*tokens)->next;
	file_tok = (*tokens)->content;
	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = AST_REDIR;
	node->data.redir.redir_type = redir;
	node->data.redir.file = ft_strdup(file_tok->text);
	node->data.redir.child = NULL;
	*tokens = (*tokens)->next;
	return (node);
}
