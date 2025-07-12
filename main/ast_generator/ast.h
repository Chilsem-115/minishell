#ifndef AST_SIMPLE_H
# define AST_SIMPLE_H

typedef enum e_node_type
{
	NODE_CMD,
	NODE_REDIR,
	NODE_CTRL
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				*text;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

void	ast_free_node(t_ast_node *node);
void	ast_free(t_ast_node *root);
void	ast_set_children(t_ast_node *parent, t_ast_node *left, t_ast_node *right);

t_ast_node	*ast_new_node(t_node_type type, const char *text);
t_ast_node	*ast_insert_pipe(t_ast_node *left, t_ast_node *right);
#endif
