/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:29:53 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:30:31 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	set_ctrl_branch(t_ast_node *ctrl, t_ast_node *left, t_ast_node *right)
{
	if (!ctrl || ctrl->type != AST_CONTROL)
		return ;
	ctrl->data.ctrl.left = left;
	ctrl->data.ctrl.right = right;
}

void	set_redir_child(t_ast_node *redir, t_ast_node *child)
{
	if (redir && redir->type == AST_REDIR)
		redir->data.redir.child = child;
}

int	is_control(t_list *token)
{
	t_token	*tok;

	if (!token || !token->content)
		return (0);
	tok = (t_token *)token->content;
	return (tok->type == TOK_PIPE);
}

int	is_redir(t_list *token)
{
	t_token	*tok;

	if (!token || !token->content)
		return (0);
	tok = (t_token *)token->content;
	return (
		tok->type == TOK_REDIR_IN ||
		tok->type == TOK_REDIR_OUT ||
		tok->type == TOK_REDIR_APPEND ||
		tok->type == TOK_HEREDOC
	);
}
