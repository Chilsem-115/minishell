
#include "tokenize.h"
#include "expansion.h"
#include <stdlib.h>

/* returns a new string with all SQ/DQ sentinels removed */
char	*remove_syntactic_sentinels(const char *s)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s)
		return (NULL);
	out = malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != SQ_SENTINEL && s[i] != DQ_SENTINEL)
		{
			out[j] = s[i];
			j++;
		}
		i++;
	}
	out[j] = '\0';
	return (out);
}

/* strip on a single token (WORD only) */
static void	strip_on_token(t_token *tok)
{
	char	*clean;

	if (!tok || tok->type != TOK_WORD || !tok->text)
		return ;
	clean = remove_syntactic_sentinels(tok->text);
	if (!clean)
		tokenizer_error(ERR_MEMORY);
	free(tok->text);
	tok->text = clean;
}

/* run AFTER expansion -> splitting (unquoted) -> globbing */
void	strip_sentinels_post_expansion(t_list *lst)
{
	t_token		*tok;
	t_tokentype	prev;

	prev = TOK_WORD;
	while (lst)
	{
		tok = (t_token *)lst->content;
		if (tok && prev != TOK_HEREDOC)
			strip_on_token(tok);
		if (tok)
			prev = tok->type;
		lst = lst->next;
	}
}
