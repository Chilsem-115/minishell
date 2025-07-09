
/* ast.h */

#ifndef AST_H
# define AST_H

# include "tokenize.h"
# include "libft.h"

/* */
typedef struct s_cmd_data
{
	char		*cmd;
	t_list		*args;
}	t_cmd_data;

/* */
typedef struct s_redir_data
{
	char		*file;
}	t_redir_data;

/* */
typedef union u_ast_data
{
	t_cmd_data	cmd;
	t_redir_data	redir;
}	t_ast_data;

/* */
typedef struct s_ast_node
{
	t_tokentype			type;
	t_ast_data			data;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

/* */
t_ast_node	*ast_node_new_cmd(const char *cmd, t_list *args);
t_ast_node	*ast_node_new_redir(t_tokentype type, const char *file);
void		free_ast(t_ast_node *root);

#endif
