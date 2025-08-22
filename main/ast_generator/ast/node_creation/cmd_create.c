
#include "ast.h"

static t_ast_node	*consume_leading_redirs(t_list **tokens,
		t_ast_node **redir_chain)
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
	cmd_node = ft_calloc(1, sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = AST_COMMAND;
	cmd_node->data.cmd.text = tokens_to_argv(*tokens);
	while (*tokens && is_valid_cmd_token(((t_token *)(*tokens)->content)->type))
		*tokens = (*tokens)->next;
	return (cmd_node);
}

static t_ast_node	*make_empty_cmd(void)
{
	t_ast_node	*n;

	n = ft_calloc(1, sizeof(*n));
	if (!n)
		return (NULL);
	n->type = AST_COMMAND;
	return (n);
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
	{
		if (redir_chain)
		{
			cmd_node = make_empty_cmd();
			if (!cmd_node)
				return (NULL);
			set_redir_child(redir_chain, cmd_node);
			return (redir_chain);
		}
		return (NULL);
	}
	if (redir_chain)
	{
		set_redir_child(redir_chain, cmd_node);
		return (redir_chain);
	}
	return (cmd_node);
}
