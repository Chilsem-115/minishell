
#include <stdlib.h>
#include "ast.h"

t_ast_node	*ast_node_new_cmd(const char *cmd, t_list *args)
{
	t_cmd_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
}

t_ast_node	*ast_node_new_redir(t_tokentype type, const char *file, t_ast_node *child)
{
	t_ast_node	*
}


t_ast_node	*ast_node_new_ctrl(t_tokentype op, t_ast_node *left, t_ast_node *right)
{
}
