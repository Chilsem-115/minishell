
#include "ast.h"

void	set_ctrl_branch(t_ast_node *ctrl, t_ast_node *left, t_ast_node *right)
{
	if (!ctrl || ctrl->type != AST_CONTROL)
		return;
	ctrl->data.ctrl.left = left;
	ctrl->data.ctrl.right = right;
}

void	set_redir_child(t_ast_node *redir, t_ast_node *child)
{
	if (redir && redir->type == AST_REDIR)
		redir->data.redir.child = child;
}

int	is_control(t_ast_node *node)
{
	return (node && node->type == AST_CONTROL);
}

int	is_redir(t_ast_node *node)
{
	return (node && node->type == AST_REDIR);
}
