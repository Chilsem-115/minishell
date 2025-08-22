/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:20:55 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/22 17:52:13 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"
#include <signal.h>
#include <sys/types.h>

void	check(t_context *ctx)
{
	if (exec_check(ctx->argv[0]) == 1)
	{
		execve(ctx->argv[0], ctx->argv, my_env(ctx));
		ft_dprintf(2, "%s: No such file or directory\n", ctx->argv[0]);
		exit(127);
	}
	ctx->path = check_exec(ctx->argv[0], ctx);
	if (!ctx->path)
	{
		ft_dprintf(2, "%s: command not found\n", ctx->argv[0]);
		exit(127);
	}
}

static int	help_func(t_context *ctx)
{
	pid_t		pid;
	static void	(*oldhdl_int)(int);
	static void	(*oldhdl_quit)(int);

	oldhdl_int = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN),
			1);
	oldhdl_quit = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT,
				SIG_IGN), 2);
	pid = fork();
	if (pid == 0)
	{
		close(ctx->fd[0]);
		close(ctx->fd[1]);
		signal(SIGINT, oldhdl_int);
		signal(SIGQUIT, oldhdl_quit);
		check(ctx);
		execve(ctx->path, ctx->argv, my_env(ctx));
		perror(" execve");
		exit(126);
	}
	return (pid);
}

void	command(t_context *ctx)
{
	pid_t	pid;

	if (ctx->ast->data.cmd.text)
		ctx->argv = ctx->ast->data.cmd.text;
	else
		ctx->argv = NULL;
	if (handle_builtin(ctx))
		return ;
	pid = help_func(ctx);
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	waitpid(pid, &ctx->stat, 0);
	if (WIFSIGNALED(ctx->stat))
	{
		if (WTERMSIG(ctx->stat) == SIGINT || WTERMSIG(ctx->stat) == SIGQUIT)
			write(1, "\n", 1);
		get_exit_status(WTERMSIG(ctx->stat) + 128, 0);
	}
	else
		get_exit_status(WEXITSTATUS(ctx->stat), 0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_ast_node(t_context *ctx, t_ast_node *node)
{
	if (!node)
	{
		// ft_dprintf(2, "invalid '|' or redir ... \n");
		return ;
	}
	if (node->type == AST_REDIR)
	{
		redirections(node);
		node = node->data.redir.child;
	}
	if (node->type == AST_CONTROL && node->data.ctrl.op == CTRL_PIPE)
	{
		ctx->p = 1;
		ctx->ast = node;
		pipline(ctx);
	}
	else if (node->type == AST_COMMAND)
	{
		ctx->ast = node;
		pipe_command(ctx);
	}
}

void	command_exec(t_context *ctx)
{
	ctx->fd[0] = dup(0);
	ctx->fd[1] = dup(1);
	if (!ctx->ast)
		return ;
	if (ctx->ast->type == AST_REDIR)
	{
		redirections(ctx->ast);
		while (ctx->ast && ctx->ast->type != AST_COMMAND)
			ctx->ast = ctx->ast->data.redir.child;
	}
	if (ctx->ast->type == AST_COMMAND)
		command(ctx);
	else
	{
		ctx->input_fd = STDIN_FILENO;
		exec_ast_node(ctx, ctx->ast);
	}
	dup2(ctx->fd[0], 0);
	dup2(ctx->fd[1], 1);
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	ctx->p = 0;
}
