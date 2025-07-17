
#include "ast.h"
#include <stdlib.h>

t_ast_node	*make_command(const char *name, t_list *flags, t_list *args)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_COMMAND;
	node->data.cmd.name = ft_strdup(name);
	node->data.cmd.flags = flags;
	node->data.cmd.args = args;
	return (node);
}

t_ast_node	*make_redir(t_redir_type redir_type, const char *file,
					t_ast_node *child)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_REDIR;
	node->data.redir.redir_type = redir_type;
	node->data.redir.file = ft_strdup(file);
	node->data.redir.child = child;
	return (node);
}

t_ast_node	*make_ctrl(t_ctrl_op op, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = AST_CONTROL;
	node->data.ctrl.op = op;
	node->data.ctrl.left = left;
	node->data.ctrl.right = right;
	return (node);
}
