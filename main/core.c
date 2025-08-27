/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:34 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/27 01:25:29 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"
#include "expansion.h"
#include "execute.h"

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
	if (!ctx->tokens)
		return ;
	expand_variables(ctx);
	ctx->ast = generate_ast(ctx->tokens);
	if (!ctx->ast)
		return ;
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
	char	*line;

	while (1)
	{
		line = ft_readline();
		ctx->line = ft_strdup(line);
		free(line);
		if (*ctx->line)
			handle_line(ctx);
		ft_lstclear_gc(&ctx->tokens, free_token);
		if (ctx->ast)
			ast_clear(&ctx->ast);
	}
}
