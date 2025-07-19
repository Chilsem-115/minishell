#ifndef AST_SIMPLE_H
# define AST_SIMPLE_H

# include "tokenize.h"
# include <stdlib.h>

typedef enum	e_ast_type
{
	AST_COMMAND,
	AST_REDIR,
	AST_CONTROL
}	t_ast_type;

typedef enum	e_ctrl_op
{
	CTRL_PIPE
}	t_ctrl_op;

typedef enum	e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct	s_cmd_node
{
	char	*name;
	char	*flags;
	t_list	*args;
}	t_cmd_node;

typedef struct	s_redir_node
{
	t_redir_type		redir_type;
	char				*file;
	struct s_ast_node	*child;
}	t_redir_node;

typedef struct	s_ctrl_node
{
	t_ctrl_op			op;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ctrl_node;

typedef union	u_ast_data
{
	t_cmd_node		cmd;
	t_redir_node	redir;
	t_ctrl_node		ctrl;
}	t_ast_data;

typedef struct	s_ast_node
{
	t_ast_type	type;
	t_ast_data	data;
}	t_ast_node;

#endif
