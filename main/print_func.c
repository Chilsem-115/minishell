
#include "messh.h"
#include "tokenize.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Forward */
static void			print_node(t_ast_node *node, int depth, int is_last);

/* ------------------------- TOKEN LIST PRINTER ------------------------- */

static const char	*token_type_str(t_tokentype type)
{
	if (type == TOK_WORD)
		return ("TOK_WORD");
	if (type == TOK_PIPE)
		return ("TOK_PIPE");
	if (type == TOK_REDIR_IN)
		return ("TOK_REDIR_IN");
	if (type == TOK_HEREDOC)
		return ("TOK_HEREDOC");
	if (type == TOK_REDIR_OUT)
		return ("TOK_REDIR_OUT");
	if (type == TOK_REDIR_APPEND)
		return ("TOK_REDIR_APPEND");
	return ("TOK_UNKNOWN");
}

void	print_token_list(t_list *tokens)
{
	const char	*type_str;
	t_token		*tok;

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

/* --------------------------- AST TREE PRINTER (to STDERR) ------------- */

static void	print_indent(int depth, int is_last)
{
	int	i;

	i = 0;
	while (i < (depth > 0 ? depth - 1 : 0))
	{
		dprintf(STDERR_FILENO, "│   ");
		i++;
	}
	if (depth > 0)
		dprintf(STDERR_FILENO, "%s── ", is_last ? "└" : "├");
}

static void	print_labeled_value(int depth, int is_last, const char *label,
		const char *value)
{
	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "%s%s\n", label, value ? value : "(null)");
}

static const char	*redir_label(int t)
{
	static const char	*label[] = {"<", ">", ">>", "<<"};

	if (t >= 0 && t < 4)
		return (label[t]);
	return ("(invalid)");
}

static const char	*ctrl_label(int op)
{
	static const char	*label[] = {"|", "||", "&&"};

	if (op >= 0 && op < 3)
		return (label[op]);
	return ("(invalid)");
}

static void	print_command_line(t_cmd_node *cmd, int depth, int is_last)
{
	int	i;

	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "CMD:");
	if (!cmd->text)
	{
		dprintf(STDERR_FILENO, " (null)\n");
		return ;
	}
	i = 0;
	while (cmd->text[i])
	{
		dprintf(STDERR_FILENO, " [%s]", cmd->text[i]);
		i++;
	}
	dprintf(STDERR_FILENO, "\n");
}

static void	print_redir_line(t_redir_node *redir, int depth, int is_last)
{
	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "REDIR: %s\n", redir_label(redir->redir_type));
}

static void	print_ctrl_line(t_ctrl_node *ctrl, int depth, int is_last)
{
	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "CTRL: %s\n", ctrl_label(ctrl->op));
}

static void	print_root_line(int depth, int is_last)
{
	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "ROOT\n");
}

static void	print_node(t_ast_node *node, int depth, int is_last)
{
	if (!node)
		return ;
	if (node->type == AST_ROOT)
	{
		print_root_line(depth, is_last);
		if (node->data.ctrl.left && node->data.ctrl.right)
		{
			print_node(node->data.ctrl.left, depth + 1, 0);
			print_node(node->data.ctrl.right, depth + 1, 1);
		}
		else if (node->data.ctrl.left)
			print_node(node->data.ctrl.left, depth + 1, 1);
		else if (node->data.ctrl.right)
			print_node(node->data.ctrl.right, depth + 1, 1);
		return ;
	}
	if (node->type == AST_COMMAND)
	{
		print_command_line(&node->data.cmd, depth, is_last);
		return ;
	}
	if (node->type == AST_REDIR)
	{
		print_redir_line(&node->data.redir, depth, is_last);
		if (node->data.redir.child)
		{
			print_labeled_value(depth + 1, 0, "File: ", node->data.redir.file);
			print_node(node->data.redir.child, depth + 1, 1);
		}
		else
			print_labeled_value(depth + 1, 1, "File: ", node->data.redir.file);
		return ;
	}
	if (node->type == AST_CONTROL)
	{
		print_ctrl_line(&node->data.ctrl, depth, is_last);
		if (node->data.ctrl.left && node->data.ctrl.right)
		{
			print_node(node->data.ctrl.left, depth + 1, 0);
			print_node(node->data.ctrl.right, depth + 1, 1);
		}
		else if (node->data.ctrl.left)
			print_node(node->data.ctrl.left, depth + 1, 1);
		else if (node->data.ctrl.right)
			print_node(node->data.ctrl.right, depth + 1, 1);
		return ;
	}
	print_indent(depth, is_last);
	dprintf(STDERR_FILENO, "UNKNOWN NODE TYPE\n");
}

void	print_ast(t_ast_node *node)
{
	print_node(node, 0, 1);
}
