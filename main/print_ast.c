
#include <stdio.h>
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
	{
		printf("ROOT\n");
		if (node->data.ctrl.left)
			print_node(node->data.ctrl.left, depth + 1, 1);
	}
	else if (node->type == AST_COMMAND)
	{
		printf("CMD: %s\n", node->data.cmd.name);
		if (node->data.cmd.flags && *node->data.cmd.flags)
		{
			print_indent(depth + 1, 0);
			printf("Flags: -%s\n", node->data.cmd.flags);
		}

		if (node->data.cmd.args)
		{
			print_indent(depth + 1, 1);
			printf("Args:");
			t_list *arg = node->data.cmd.args;
			while (arg)
			{
				t_token *tok = (t_token *)arg->content;
				printf(" %s", tok->text);
				arg = arg->next;
			}
			printf("\n");
		}
	}
	else if (node->type == AST_REDIR)
	{
		const char *redir_type[] = { "<", "<<", ">", ">>" };
		printf("REDIR: %s\n", redir_type[node->data.redir.redir_type]);

		// Print file
		print_indent(depth + 1, 0);
		printf("File: %s\n", node->data.redir.file);

		// Print child
		if (node->data.redir.child)
			print_node(node->data.redir.child, depth + 1, 1);
	}
	else if (node->type == AST_CONTROL)
	{
		const char *op[] = { "|", "||", "&&" };
		printf("CTRL: %s\n", op[node->data.ctrl.op]);

		if (node->data.ctrl.left)
			print_node(node->data.ctrl.left, depth + 1, 0);
		if (node->data.ctrl.right)
			print_node(node->data.ctrl.right, depth + 1, 1);
	}
}

void	print_ast(t_ast_node *node)
{
	print_node(node, 0, 1);
}
