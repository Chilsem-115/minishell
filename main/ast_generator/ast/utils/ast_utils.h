
#ifndef AST_UTILS_H
# define AST_UTILS_H

# include "ast.h"
# include "tokenize.h"

/* Mapping functions */
t_ctrl_op		map_ctrl_type(t_tokentype type);
t_redir_type	map_redir_type(t_tokentype type);

/* Type checking */
int				is_control_token(t_list *token);
int				is_redir_token(t_list *token);

#endif
