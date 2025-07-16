
#ifndef AST_SIMPLE_H
# define AST_SIMPLE_H

# include "tokenize.h"
# include <stdlib.h>

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_REDIR,
	AST_CONTROL
}	t_ast_type;

typedef struct s_cmd_node
{
	char	*name;
	t_list	*flags;
	t_list	*args;
}	t_cmd_node;

typedef struct s_redir_node
{
	t_tokentype			redir_type;
	char				*file;
	struct s_ast_node	*child;
}	t_redir_node;

typedef struct s_ctrl_node
{
	t_tokentype			op;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ctrl_node;

typedef union u_ast_data
{
	t_cmd_node		cmd;
	t_redir_node	redir;
	t_ctrl_node		ctrl;
}	t_ast_data;

typedef struct s_ast_node
{
	t_ast_type	type;
	t_ast_data	data;
}	t_ast_node;

#endif
