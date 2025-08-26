/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 05:03:27 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 05:03:41 by itamsama         ###   ########.fr       */
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

static void	ft_lstdelone_gc(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		ft_free(lst);
	}
}

void	ft_lstclear_gc(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_gc(*lst, del);
		(*lst) = tmp;
	}
	*lst = NULL;
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
