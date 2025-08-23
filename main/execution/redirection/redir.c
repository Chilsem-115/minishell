/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:29:35 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/23 21:54:49 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execute.h"
#include "libft.h"
#include "messh.h"

int	red_in(t_ast_node *ast)
{
	int	fd;

	fd = open(ast->data.redir.file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, 0) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

static int	red_out(t_ast_node *ast)
{
	int	fd;

	fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

static int	red_append(t_ast_node *ast)
{
	int	fd;

	fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, 1) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(fd);
	return (0);
}

int	redirections(t_ast_node *ast)
{
	if (!ast)
		return (0);
	if (redirections(ast->data.redir.child) == 1)
		return (1);
	if (ast->type == AST_REDIR)
	{
		if (ast->data.redir.redir_type == REDIR_IN
			|| ast->data.redir.redir_type == REDIR_HEREDOC)
			return(red_in(ast));
		else if (ast->data.redir.redir_type == REDIR_OUT)
			return(red_out(ast));
		else if (ast->data.redir.redir_type == REDIR_APPEND)
			return(red_append(ast));
	}
	return (0);
}
