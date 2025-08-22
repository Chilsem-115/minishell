/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:23:20 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/19 23:23:21 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"

void	*ft_malloc(t_list **garbage, size_t size)
{
	void	*p;
	t_list	*newnode;

	p = malloc(size);
	if (!p)
	{
		ft_lstclear(garbage, free);
		exit(1);
	}
	newnode = ft_lstnew(p);
	if (!newnode)
	{
		free(p);
		ft_lstclear(garbage, free);
		exit(1);
	}
	ft_lstadd_back(garbage, newnode);
	return (p);
}

void	*garbage_coll(int f, size_t size)
{
	static t_list	*garbage;

	if (f == 0)
		return (ft_malloc(&garbage, size));
	else if (f == 1)
		ft_lstclear(&garbage, free);
	return (NULL);
}

void	if_command(t_ast_node *ast)
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
		if_command(ast);
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
