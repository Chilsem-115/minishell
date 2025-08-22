/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:59:28 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/24 16:30:11 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"
# include "tokenize.h"
# include <stdlib.h>

/* abstract syntax tree node types */
typedef enum e_ast_type
{
	AST_COMMAND,
	AST_REDIR,
	AST_CONTROL,
	AST_ROOT
}						t_ast_type;

/* control operations */
typedef enum e_ctrl_op
{
	CTRL_INVALID = -1,
	CTRL_PIPE
}						t_ctrl_op;

/* redirection operations */
typedef enum e_redir_type
{
	REDIR_INVALID = -1,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}						t_redir_type;

/* command node */
typedef struct s_cmd_node
{
	char				**text;
}						t_cmd_node;

/* redirection node */
typedef struct s_redir_node
{
	t_redir_type		redir_type;
	char				*file;
	struct s_ast_node	*child;
}						t_redir_node;

/* control node*/
typedef struct s_ctrl_node
{
	t_ctrl_op			op;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ctrl_node;

/* ast_union */
typedef union u_ast_data
{
	t_cmd_node			cmd;
	t_redir_node		redir;
	t_ctrl_node			ctrl;
}						t_ast_data;

/* general node */
typedef struct s_ast_node
{
	t_ast_type			type;
	t_ast_data			data;
}						t_ast_node;

/* ast manipulation functions */
void					set_ctrl_branch(t_ast_node *ctrl, t_ast_node *left,
							t_ast_node *right);
void					set_redir_child(t_ast_node *redir, t_ast_node *child);
int						is_control(t_list *token);
int						is_redir(t_list *token);

/* create_node */
t_ast_node				*make_cmd(t_list **tokens);
t_ast_node				*make_ctrl(t_list **tokens);
t_ast_node				*make_redir(t_list **tokens);

/* cmd_node creation utils */
int						is_valid_cmd_token(t_tokentype type);
char					*extract_flags(t_list **tokens);
char					**tokens_to_argv(t_list *tokens);

/* type mapping */
t_ctrl_op				map_ctrl_type(t_tokentype type);
t_redir_type			map_redir_type(t_tokentype type);

#endif
