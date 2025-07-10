
#include <stdlib.h>
#include "ast.h"

t_ast_node	*ast_node_new_cmd(const char *cmd, t_list *args)
{
	t_ast_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = TOK_WORD;
	node->data.cmd.name = strdup_safe(name);
	node->data.cmd.args = args;
	node->left = NULL;
	node->right = NULL;
}
