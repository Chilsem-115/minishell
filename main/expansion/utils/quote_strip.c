/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_strip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:37:49 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 22:43:42 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "expansion.h"
#include <stdlib.h>
#include "execute.h"

/* returns a new string with all SQ/DQ sentinels removed */
char	*remove_syntactic_sentinels(const char *s)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s)
		return (NULL);
	out = garbage_coll(0, ft_strlen(s) + 1);
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

char	*remove_qouts(const char *s)
{
	size_t	i;
	size_t	j;
	char	q;
	char	*out;

	if (!s)
		return (NULL);
	out = garbage_coll(0, ft_strlen(s) + 1);
	i = 0;
	j = 0;
	q = 0;
	while (s[i])
	{
		if (q == 0 && (s[i] == '\'' || s[i] == '\"'))
			q = s[i];
		else if (q != 0 && s[i] == q)
			q = 0;
		else
			out[j++] = s[i];
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
		return ;
	ft_free(tok->text);
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
