/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:57:28 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/25 19:49:51 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

void	left_cmd(t_context *ctx, int *pipefd)
{
	if (ctx->var->input_fd != STDIN_FILENO)
	{
		dup2(ctx->var->input_fd, STDIN_FILENO);
		close(ctx->var->input_fd);
	}
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	ctx->var->input_fd = STDIN_FILENO;
	exec_ast_node(ctx, ctx->ast->data.ctrl.left);
	close(0);
	close(1);
	ft_exit(1);
}

void	right(t_context *ctx, int *pipefd)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	ctx->var->input_fd = STDIN_FILENO;
	exec_ast_node(ctx, ctx->ast->data.ctrl.right);
	close(0);
	close(1);
	ft_exit(1);
}

void	setup_signals(void (**oldhdl_int)(int), void (**oldhdl_quit)(int))
{
	*oldhdl_int = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT,
				SIG_IGN), 1);
	*oldhdl_quit = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT,
				SIG_IGN), 2);
}
