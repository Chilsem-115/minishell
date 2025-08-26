/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:35:08 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:35:27 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "messh.h"

static void	replace(char *text, char old, char new)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] == old)
			text[i] = new;
		i++;
	}
}

char	*expand_token_text(char *text, t_context *ctx)
{
	char	*expanded;
	int		pos;
	t_emode	mode;

	expanded = ft_strdup(text);
	if (!expanded)
		return (NULL);
	pos = 0;
	while (1)
	{
		pos = next_dollar(expanded, pos, &mode);
		if (pos < 0)
			break ;
		if (replace_one_at(&expanded, pos, ctx) < 0)
		{
			ft_free(expanded);
			return (NULL);
		}
		pos++;
	}
	return (expanded);
}

static int	expand_and_splice(t_list **head, t_list *node, t_context *ctx)
{
	t_token	*tok;
	char	*text;
	t_list	*sub;

	if (!head || !*head || !node || !ctx)
		return (-1);
	tok = (t_token *)node->content;
	if (!tok || tok->type != TOK_WORD || !tok->text)
		return (0);
	text = expand_token_text(tok->text, ctx);
	if (!text)
		return (-1);
	sub = tokenize_nomark(text);
	ft_free(text);
	lst_replace_node(head, node, sub);
	return (0);
}

void	expand_variables(t_context *ctx)
{
	t_list	*curr;
	t_list	*next;
	int		status;

	if (!ctx || !ctx->tokens)
		return ;
	curr = ctx->tokens;
	while (curr)
	{
		next = curr->next;
		if (((t_token *)curr->content)->expand)
		{
			status = expand_and_splice(&ctx->tokens, curr, ctx);
			if (status < 0)
				return ;
		}
		else if (((t_token *)curr->content)->expand == 0)
		{
			replace(((t_token *)curr->content)->text, '\x01', '\'');
			replace(((t_token *)curr->content)->text, '\x02', '\"');
		}
		curr = next;
	}
	strip_sentinels_post_expansion(ctx->tokens);
}
