
#include "libft.h"
#include "tokenize.h"
#include "ast.h"


t_redir_type	map_redir_type(t_tokentype type)
{
	if (type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOK_REDIR_APPEND)
		return (REDIR_APPEND);
	if (type == TOK_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

t_ctrl_op	map_ctrl_type(t_tokentype type)
{
	if (type == TOK_PIPE)
		return (CTRL_PIPE);
	return (-1);
}
