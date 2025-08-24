#include "expansion.h"
#include "tokenize.h"
#include "libft.h"



/* Local append that does NOT rely on ft_lstadd_back (avoids list bugs) */

static void	append_node(t_list **head, t_list **tail, t_list *node)

{

	if (!node)

		return ;

	if (*tail)

		(*tail)->next = node;

	else

		*head = node;

	while (node->next)

		node = node->next;

	*tail = node;

}



static int	is_ifs(char c)

{

	return (c == ' ' || c == '\t' || c == '\n');

}



static int	has_next(const char *s, size_t i)

{

	return (s[i] && s[i + 1]);

}



static int	is_op2(const char *s, size_t i, char a, char b)

{

	return (s[i] == a && s[i + 1] == b);

}



static void	push_word(t_list **out, t_list **tail, const char *s, size_t a, size_t b)

{

	char	*dup;

	t_token	*tok;

	t_list	*node;



	if (b <= a)

		return ;

	dup = ft_strndup(s + a, b - a);

	if (!dup)

		return ;

	tok = (t_token *)malloc(sizeof(*tok));

	if (!tok)

	{

		free(dup);

		return ;

	}

	tok->text = dup;

	tok->type = TOK_WORD;

	node = ft_lstnew(tok);

	if (!node)

	{

		free(dup);

		free(tok);

		return ;

	}

	append_node(out, tail, node);

}



static void	push_op(t_list **out, t_list **tail, t_tokentype type)

{

	t_token	*tok;

	t_list	*node;



	tok = (t_token *)malloc(sizeof(*tok));

	if (!tok)

		return ;

	tok->text = NULL;

	tok->type = type;

	node = ft_lstnew(tok);

	if (!node)

	{

		free(tok);

		return ;

	}

	append_node(out, tail, node);

}



/* Split expanded text into tokens:

   - IFS splitting (space, tab, newline)

   - operators: |  <  >  <<  >>

   - quotes inside expanded text are ordinary bytes */

t_list	*refactor(const char *text)

{

	size_t	i;

	size_t	start;

	t_list	*out;

	t_list	*tail;



	if (!text || !*text)

		return (NULL);

	out = NULL;

	tail = NULL;

	i = 0;

	while (text[i])

	{

		while (text[i] && is_ifs(text[i]))

			i++;

		if (!text[i])

			break ;

		/* operators first (single and double) */

		if (text[i] == '|')

		{

			push_op(&out, &tail, TOK_PIPE);

			i++;

			continue ;

		}

		if (has_next(text, i) && is_op2(text, i, '<', '<'))

		{

			push_op(&out, &tail, TOK_HEREDOC);

			i += 2;

			continue ;

		}

		if (has_next(text, i) && is_op2(text, i, '>', '>'))

		{

			push_op(&out, &tail, TOK_REDIR_APPEND);

			i += 2;

			continue ;

		}

		if (text[i] == '<')

		{

			push_op(&out, &tail, TOK_REDIR_IN);

			i++;

			continue ;

		}

		if (text[i] == '>')

		{

			push_op(&out, &tail, TOK_REDIR_OUT);

			i++;

			continue ;

		}

		/* word */

		start = i;

		while (text[i]

			&& !is_ifs(text[i])

			&& text[i] != '|' && text[i] != '<' && text[i] != '>')

			i++;

		push_word(&out, &tail, text, start, i);

	}

	return (out);

}
