
#include "expansion.h"
#include "messh.h"

/*
static int	replace_one_at(char **expanded, int pos, t_context *ctx)
{
	char		*name;
	t_env		*node;
	char		*new_str;
	int			consumed;
	const char	*replacement;

	name = NULL;
	consumed = grab_variable(*expanded, pos, &name);
	if (consumed <= 0)
		return (-1);
	if (consumed == 0)
		return (0);
	node = env_find_node(ctx->envp, name);
	if (node && node->value)
		replacement = node->value;
	else
		replacement = "";
	new_str = str_replace_range(*expanded, (size_t)pos,
			(size_t)consumed, replacement);
	ft_free(name);
	if (!new_str)
		return (-1);
	ft_free(*expanded);
	*expanded = new_str;
	return (1);
}
*/

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
