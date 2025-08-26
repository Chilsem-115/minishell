/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:59:14 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:59:38 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	is_valid_cmd_token(t_tokentype type)
{
	return (type == TOK_WORD);
}

static int	count_valid_tokens(t_list *tokens)
{
	int		count;
	t_token	*tok;

	count = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (!tok || !is_valid_cmd_token(tok->type))
			break ;
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static int	fill_argv(char **argv, t_list *tokens)
{
	int		i;
	t_token	*tok;

	i = 0;
	while (tokens)
	{
		tok = tokens->content;
		if (!tok || !is_valid_cmd_token(tok->type))
			break ;
		argv[i] = ft_strdup(tok->text);
		if (!argv[i])
			return (1);
		tokens = tokens->next;
		i++;
	}
	return (0);
}

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
		ft_free(tmp);
		if (!flags)
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (deldup(flags));
}

char	**tokens_to_argv(t_list *tokens)
{
	char	**argv;
	int		count;

	count = count_valid_tokens(tokens);
	argv = ft_calloc(count + 1, sizeof(char *));
	if (fill_argv(argv, tokens))
		return (NULL);
	return (argv);
}
