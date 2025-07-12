
#include <stdlib.h>
#include "ast.h"

t_ast_node	*ast_new_node(t_node_type type, const char *text)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (!text)
		node->text = NULL;
	else
		node->text = strdup(text);
	node->left = NULL;
	node->right = NULL;
}

void	ast_free_node(t_ast_node *node)
{
	if (!node)
		return ;
	free(node->text);
	free(node);
}

void	ast_free(t_ast_node	*root)
{
	if (!root)
		return ;
	ast_free(root->left);
	ast_free(root->right);
	ast_free_node(root);
}

void	ast_set_children(t_ast_node *parent, t_ast_node *left, t_ast_node *right)
{
	if (!parent)
		return ;
	parent->left = left;
	parent->right = right;
}

t_ast_node	*ast_insert_pipe(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe;

	pipe = ast_new_node(NODE_CTRL, "|");
	if (!pipe)
		return (NULL);
	ast_set_children(pipe, left, right);
	return (pipe);
}
