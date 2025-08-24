
#include "tokenize.h"


static const char	*tok_display(const t_token *t)
{
	if (!t)
		return ("newline");
	if (t->type == TOK_WORD)
	{
		if (t->text && t->text[0])
			return (t->text);
		return ("newline");
	}
	if (t->type == TOK_PIPE)
		return ("|");
	if (t->type == TOK_REDIR_IN)
		return ("<");
	if (t->type == TOK_REDIR_OUT)
		return (">");
	if (t->type == TOK_HEREDOC)
		return ("<<");
	if (t->type == TOK_REDIR_APPEND)
		return (">>");
	return ("newline");
}

const char	*find_redir_error_token(t_list *lst)
{
	t_token	*cur;
	t_token	*next;

	while (lst)
	{
		cur = (t_token *)lst->content;
		if (cur && (cur->type == TOK_REDIR_IN
				|| cur->type == TOK_HEREDOC
				|| cur->type == TOK_REDIR_OUT
				|| cur->type == TOK_REDIR_APPEND))
		{
			if (!lst->next)
				return (tok_display(cur));
			next = (t_token *)lst->next->content;
			if (!next)
				return (tok_display(cur));
			if (next->type != TOK_WORD)
				return (tok_display(next));
		}
		lst = lst->next;
	}
	return (NULL);
}

const char	*find_pipe_error_token(t_list *tokens)
{
	t_list	*node;
	t_token	*tok;

	if (!tokens)
		return (NULL);
	tok = (t_token *)tokens->content;
	if (tok && tok->type == TOK_PIPE)
		return ("|");
	node = tokens;
	while (node && node->next)
	{
		tok = (t_token *)node->content;
		if (tok && tok->type == TOK_PIPE)
		{
			tok = (t_token *)node->next->content;
			if (tok && tok->type == TOK_PIPE)
				return ("|");
		}
		node = node->next;
	}
	tok = (t_token *)node->content;
	if (tok && tok->type == TOK_PIPE)
		return ("newline");
	return (NULL);
}
