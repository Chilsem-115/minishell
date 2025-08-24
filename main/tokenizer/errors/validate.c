
#include "tokenize.h"

/* checks that there is no unclosed quotes*/
int	validate_quotes_line(const char *s)
{
	int	in_sq;
	int	in_dq;

	if (!s)
		return (1);
	in_sq = 0;
	in_dq = 0;
	while (*s)
	{
		if (!in_dq && *s == '\'')
			in_sq = !in_sq;
		else if (!in_sq && *s == '"')
			in_dq = !in_dq;
		s++;
	}
	return (in_sq == 0 && in_dq == 0);
}

int	validate_redirs(t_list *lst)
{ t_token	*cur;
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
				return (0);
			next = (t_token *)lst->next->content;
			if (!next || next->type != TOK_WORD)
				return (0);
		}
		lst = lst->next;
	}
	return (1);
}

/* checks that there is no 2 pipes followed by each other*/
int	validate_pipes(t_list *tokens)
{
	t_token	*tok;
	t_list	*node;

	if (!tokens)
		return (1);
	tok = (t_token *)tokens->content;
	if (tok && tok->type == TOK_PIPE)
		return (0);
	node = tokens;
	while (node && node->next)
	{
		tok = (t_token *)node->content;
		if (tok && tok->type == TOK_PIPE)
		{
			tok = (t_token *)node->next->content;
			if (tok && tok->type == TOK_PIPE)
				return (0);
		}
		node = node->next;
	}
	tok = (t_token *)node->content;
	if (tok && tok->type == TOK_PIPE)
		return (0);
	return (1);
}
