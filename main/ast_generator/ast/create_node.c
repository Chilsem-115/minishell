/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:32:08 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/24 16:29:01 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_ast_node	*consume_leading_redirs(t_list **tokens, t_ast_node **redir_chain)
{
	t_ast_node	*redir;

	while (*tokens && is_redir(*tokens))
	{
		redir = make_redir(tokens);
		if (!redir)
			return (NULL);
		set_redir_child(redir, *redir_chain);
		*redir_chain = redir;
	}
	return (*redir_chain);
}

static t_ast_node	*make_cmd_node(t_list **tokens)
{
	t_ast_node	*cmd_node;

	if (!*tokens || !is_valid_cmd_token(((t_token *)(*tokens)->content)->type))
		return (NULL);
	cmd_node = malloc(sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = AST_COMMAND;
	cmd_node->data.cmd.text = tokens_to_argv(*tokens);
	while (*tokens && is_valid_cmd_token(((t_token *)(*tokens)->content)->type))
		*tokens = (*tokens)->next;
	return (cmd_node);
}

t_ast_node	*make_cmd(t_list **tokens)
{
	t_ast_node	*redir_chain;
	t_ast_node	*cmd_node;

	redir_chain = NULL;
	if (consume_leading_redirs(tokens, &redir_chain) == NULL && redir_chain)
		return (NULL);
	cmd_node = make_cmd_node(tokens);
	if (!cmd_node)
		return (NULL);
	if (redir_chain)
	{
		set_redir_child(redir_chain, cmd_node);
		return (redir_chain);
	}
	return (cmd_node);
}

t_ast_node	*make_ctrl(t_list **tokens)
{
	t_token		*tok;
	t_ast_node	*node;
	t_ctrl_op	op;

	if (!tokens || !*tokens)
		return (NULL);
	tok = (*tokens)->content;
	op = map_ctrl_type(tok->type);
	if (op == CTRL_INVALID)
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
	if (redir == REDIR_INVALID)
		return (NULL);
	*tokens = (*tokens)->next;
	if (!*tokens)
		return (NULL);
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
