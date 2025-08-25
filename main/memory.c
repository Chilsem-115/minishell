/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 05:02:18 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/25 06:24:00 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "messh.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->text)
		free(token->text);
	free(token);
}

void	free_env(t_context *ctx)
{
	t_env	*cur;
	t_env	*next;

	if (!ctx || !ctx->envp)
		return ;
	cur = ctx->envp;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	ctx->envp = NULL;
}

static void	free_command(t_ast_node *ast)
{
	size_t	i;

	if (ast->data.cmd.text)
	{
		i = 0;
		while (ast->data.cmd.text[i])
		{
			free(ast->data.cmd.text[i]);
			i++;
		}
		free(ast->data.cmd.text);
	}
}

void	ast_clear(t_ast_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_COMMAND)
		free_command(ast);
	else if (ast->type == AST_REDIR)
	{
		if (ast->data.redir.file)
			free(ast->data.redir.file);
		ast_clear(ast->data.redir.child);
	}
	else if (ast->type == AST_CONTROL)
	{
		ast_clear(ast->data.ctrl.left);
		ast_clear(ast->data.ctrl.right);
	}
	free(ast);
}
