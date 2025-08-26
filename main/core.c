/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:34 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/26 08:04:15 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"
#include "messh.h"

extern int	g_gsignum;

static int	is_valid_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	handle_line(t_context *ctx)
{
	t_list	*list;

	if (!is_valid_line(ctx->line))
		return ;
	ctx->tokens = tokenize(ctx->line);
	expand_variables(ctx);
	ctx->ast = generate_ast(ctx->tokens);
	list = *get_heredocs();
	while (list)
	{
		if (heredoc(list->content, ctx) == false)
		{
			*get_heredocs() = NULL;
			return ;
		}
		list = list->next;
	}
	command_exec(ctx);
	*get_heredocs() = NULL;
}

t_list	**get_heredocs(void)
{
	static t_list	*heredocs;

	return (&heredocs);
}

void	main_loop(t_context *ctx)
{
	while (1)
	{
		ctx->line = ft_readline();
		if (*ctx->line)
			handle_line(ctx);
		ft_free(ctx->line);
		ft_lstclear_gc(&ctx->tokens, free_token);
		ast_clear(ctx->ast);
	}
}
