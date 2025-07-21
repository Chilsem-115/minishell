/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:30:27 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:01:16 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "generate.h"
#include "ast.h"
#include "tokenize.h"

static t_ast_node	*reduce_redirection(t_ast_node *cmd, t_list **tokens)
{
	t_ast_node	*redir;

	while (*tokens
		&& (*tokens)->content
		&& (((t_token *)(*tokens)->content)->type == TOK_REDIR_IN
		|| ((t_token *)(*tokens)->content)->type == TOK_REDIR_OUT
				|| ((t_token *)(*tokens)->content)->type == TOK_REDIR_APPEND
				|| ((t_token *)(*tokens)->content)->type == TOK_HEREDOC))
	{
		redir = make_redir(tokens);
		if (!redir)
			return (NULL);
		set_redir_child(redir, cmd);
		cmd = redir;
	}
	return (cmd);
}

static t_ast_node	*reduce_control(t_ast_node *left, t_list **tokens)
{
	t_ast_node	*ctrl;
	t_ast_node	*right;

	while (*tokens && (*tokens)->content && is_control(*tokens))
	{
		ctrl = make_ctrl(tokens);
		if (!ctrl)
			return (NULL);
		right = make_cmd(tokens);
		if (!right)
			return (NULL);
		right = reduce_redirection(right, tokens);
		set_ctrl_branch(ctrl, left, right);
		left = ctrl;
	}
	return (left);
}

t_ast_node	*generate_ast(t_list *tokens)
{
	t_ast_node	*current;

	if (!tokens)
		return (NULL);
	current = make_cmd(&tokens);
	if (!current)
		return (NULL);
	while (tokens)
	{
		if (is_control(tokens))
			current = reduce_control(current, &tokens);
		else if (is_redir(tokens))
			current = reduce_redirection(current, &tokens);
		else
		{
			handle_parser_error(tokens);
			return (NULL);
		}
	}
	return (make_root(current));
}
