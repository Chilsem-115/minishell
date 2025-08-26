/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 05:02:18 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 00:03:05 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "messh.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token->text)
		ft_free(token->text);
	ft_free(token);
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
		ft_free(cur->key);
		ft_free(cur->value);
		ft_free(cur);
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
			ft_free(ast->data.cmd.text[i]);
			i++;
		}
		ft_free(ast->data.cmd.text);
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
			ft_free(ast->data.redir.file);
		ast_clear(ast->data.redir.child);
	}
	else if (ast->type == AST_CONTROL)
	{
		ast_clear(ast->data.ctrl.left);
		ast_clear(ast->data.ctrl.right);
	}
	ft_free(ast);
}
