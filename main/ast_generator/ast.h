/* ast.h */

#ifndef AST_H
# define AST_H

# include "tokenize.h"
# include "libft.h"

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_REDIR,
	AST_CONTROL
}	t_ast_type;

/*
** Command node structure
** Represents a simple command, with flags and arguments
*/
typedef struct s_cmd_node
{
	char	*name;
	t_list	*flags;
	t_list	*args;
}	t_cmd_node;

/*
** Redirection node structure
** Represents a redirection operation with file destination
*/
typedef struct s_redir_node
{
	t_tokentype	redir_type;
	char		*file;
	struct s_ast_node	*child;
}	t_redir_node;

/*
** Control node structure
** Represents control operations like pipes, AND, OR
*/
typedef struct s_ctrl_node
{
	t_tokentype	op;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ctrl_node;

/*
** AST node data union
** Only one of these is active depending on the node type
*/
typedef union u_ast_data
{
	t_cmd_node		cmd;
	t_redir_node	redir;
	t_ctrl_node		ctrl;
}	t_ast_data;

/*
** AST node structure
** Type-tagged node with associated data
*/
typedef struct s_ast_node
{
	t_ast_type	type;
	t_ast_data	data;
}	t_ast_node;

/* Constructors */
t_ast_node	*ast_node_new_cmd(const char *name, t_list *flags, t_list *args);
t_ast_node	*ast_node_new_redir(t_tokentype type, const char *file, t_ast_node *child);
t_ast_node	*ast_node_new_ctrl(t_tokentype op, t_ast_node *left, t_ast_node *right);

/* Memory management */
void		free_ast(t_ast_node *root);

#endif
