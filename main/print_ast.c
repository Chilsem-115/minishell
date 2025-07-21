
#include <stdio.h>
#include "tokenize.h"
#include "ast.h"
#include "ast_gen.h"
#include "messh.h"

static void	print_indent(int depth, int is_last)
{
	for (int i = 0; i < depth - 1; i++)
		printf("│   ");
	if (depth > 0)
		printf("%s── ", is_last ? "└" : "├");
}

static void	print_node(t_ast_node *node, int depth, int is_last)
{
	if (!node)
		return;

	print_indent(depth, is_last);

	if (node->type == AST_ROOT)
		printf("ROOT\n");
	else if (node->type == AST_COMMAND)
	{
		printf("CMD: %s\n", node->data.cmd.name);
	}
	else if (node->type == AST_REDIR)
	{
		const char *redir_type[] = { "<", "<<", ">", ">>" };
		printf("REDIR: %s -> %s\n",
			redir_type[node->data.redir.redir_type],
			node->data.redir.file);
	}
	else if (node->type == AST_CONTROL)
	{
		const char *op[] = { "|", "||", "&&" };
		printf("CTRL: %s\n", op[node->data.ctrl.op]);
	}

	// Recursively print children
	if (node->type == AST_ROOT && node->data.ctrl.left)
		print_node(node->data.ctrl.left, depth + 1, 1);
	else if (node->type == AST_CONTROL)
	{
		if (node->data.ctrl.left)
			print_node(node->data.ctrl.left, depth + 1, 0);
		if (node->data.ctrl.right)
			print_node(node->data.ctrl.right, depth + 1, 1);
	}
	else if (node->type == AST_REDIR && node->data.redir.child)
		print_node(node->data.redir.child, depth + 1, 1);
}

void	print_ast(t_ast_node *node)
{
	print_node(node, 0, 1);
}
