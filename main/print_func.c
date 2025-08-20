
#include <stdio.h>
#include "tokenize.h"
#include "messh.h"

static void	print_node(t_ast_node *node, int depth, int is_last);

const char	*token_type_str(t_tokentype type)
{
	if (type == TOK_WORD)
		return "TOK_WORD";
	if (type == TOK_PIPE)
		return "TOK_PIPE";
	if (type == TOK_REDIR_IN)
		return "TOK_REDIR_IN";
	if (type == TOK_HEREDOC)
		return "TOK_HEREDOC";
	if (type == TOK_REDIR_OUT)
		return "TOK_REDIR_OUT";
	if (type == TOK_REDIR_APPEND)
		return "TOK_REDIR_APPEND";
	return "TOK_UNKNOWN";
}

void	print_token_list(t_list *tokens)
{
	t_token	*tok;
	const char *type_str;

	while (tokens)
	{
		tok = (t_token *)tokens->content;
		type_str = token_type_str(tok->type);

		write(STDOUT_FILENO, type_str, strlen(type_str));
		write(STDOUT_FILENO, ": ", 2);
		if (tok->text)
			write(STDOUT_FILENO, tok->text, strlen(tok->text));
		else
			write(STDOUT_FILENO, "(none)", 6);
		write(STDOUT_FILENO, "\n", 1);

		tokens = tokens->next;
	}
}










/* THIS IS THE BIG FUNCTION BOIIII*/

static void	print_indent(int depth, int is_last)
{
	for (int i = 0; i < (depth > 0 ? depth - 1 : 0); i++)
		printf("│   ");
	if (depth > 0)
		printf("%s── ", is_last ? "└" : "├");
}

static void	print_command_node(t_cmd_node *cmd, int depth)
{
	int	i;

	print_indent(depth, 0);
	printf("CMD:");
	if (!cmd->text)
	{
		printf(" (null)\n");
		return;
	}
	i = 0;
	while (cmd->text[i])
	{
		printf(" [%s]", cmd->text[i]);
		i++;
	}
	printf("\n");
}

static void	print_redir_node(t_redir_node *redir, int depth)
{
	const char *redir_type[] = { "<", ">", ">>", "<<" };

	int type = redir->redir_type;
	print_indent(depth, 0);
	if (type >= 0 && type <= 3)
		printf("REDIR: %s\n", redir_type[type]);
	else
		printf("REDIR: (invalid type %d)\n", type);

	print_indent(depth + 1, 0);
	printf("File: %s\n", redir->file ? redir->file : "(null)");

	if (redir->child)
		print_node(redir->child, depth + 1, 1);
}

static void	print_control_node(t_ctrl_node *ctrl, int depth)
{
	const char *op[] = { "|", "||", "&&" };

	print_indent(depth, 0);
	if (ctrl->op >= 0 && ctrl->op <= 2)
		printf("CTRL: %s\n", op[ctrl->op]);
	else
		printf("CTRL: (invalid op %d)\n", ctrl->op);

	int has_right = ctrl->right != NULL;
	if (ctrl->left)
		print_node(ctrl->left, depth + 1, !has_right);
	if (ctrl->right)
		print_node(ctrl->right, depth + 1, 1);
}

static void	print_node(t_ast_node *node, int depth, int is_last)
{
	if (!node)
		return;

	print_indent(depth, is_last);

	printf("\n\n\n\n");
	switch (node->type)
	{
		case AST_ROOT:
			printf("ROOT\n");
			if (node->data.ctrl.left)
				print_node(node->data.ctrl.left, depth + 1, 1);
			else if (node->data.ctrl.right)
				print_node(node->data.ctrl.right, depth + 1, 1);
			break;

		case AST_COMMAND:
			print_command_node(&node->data.cmd, depth);
			break;

		case AST_REDIR:
			print_redir_node(&node->data.redir, depth);
			break;

		case AST_CONTROL:
			print_control_node(&node->data.ctrl, depth);
			break;

		default:
			printf("UNKNOWN NODE TYPE\n");
			break;
	}
}

void	print_ast(t_ast_node *node)
{
	print_node(node, 0, 1);
}
