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

#include "ast_gen.h"

static t_ast_node	*reduce_redirection(t_ast_node *cmd, t_list **tokens)
{
	t_ast_node	*redir;

	if (is_redir(*tokens))
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

	if (!is_control(*tokens))
		return (left);
	ctrl = make_ctrl(tokens);
	if (!ctrl)
		return (NULL);
	right = make_cmd(tokens);
	if (!right)
		return (NULL);
	right = reduce_redirection(right, tokens);
	set_ctrl_branch(ctrl, left, right);
	return (ctrl);
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
			return (NULL);//handle_parser_error(tokens));
	}
	return (make_root(current));
}
