
#include "ast.h"
#include "tokenize.h"

char	*extract_flags(t_list **tokens)
{
	char	*flags;
	t_token	*tok;
	char	*tmp;

	flags = ft_strdup("");
	if (!flags)
		return (NULL);
	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type != TOK_WORD || tok->text[0] != '-' || !tok->text[1])
			break ;
		tmp = flags;
		flags = ft_strjoin(flags, &tok->text[1]);
		free(tmp);
		if (!flags)
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (flags);
}

t_list	*extract_args(t_list **tokens)
{
	t_list	*args;
	t_token	*tok;

	args = NULL;
	while (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == TOK_PIPE || tok->type == TOK_REDIR_IN ||
			tok->type == TOK_REDIR_OUT || tok->type == TOK_REDIR_APPEND ||
			tok->type == TOK_HEREDOC)
			break ;
		ft_lstadd_back(&args, ft_lstnew(ft_strdup(tok->text)));
		*tokens = (*tokens)->next;
	}
	return (args);
}
