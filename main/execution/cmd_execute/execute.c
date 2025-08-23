/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:20:55 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/23 15:13:55 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft.h"
#include "messh.h"
#include <signal.h>
#include <sys/types.h>

static bool	check(t_context *ctx)
{
	if(!ctx->var->argv || !ctx->var->argv[0])
		return (false);
	if (exec_check(ctx->var->argv[0]) == 1)
	{
		execve(ctx->var->argv[0], ctx->var->argv, my_env(ctx));
		ft_dprintf(2, "%s: No such file or directory\n", ctx->var->argv[0]);
		exit(127);
	}
	ctx->var->path = check_exec(ctx->var->argv[0], ctx);
	if (!ctx->var->path)
	{
		ft_dprintf(2, "%s: command not found\n", ctx->var->argv[0]);
		exit(127);
	}
	return (true);
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
		close(ctx->var->fd[0]);
		close(ctx->var->fd[1]);
		signal(SIGINT, oldhdl_int);
		signal(SIGQUIT, oldhdl_quit);
		if(check(ctx) == false)
			return(-42);
		execve(ctx->var->path, ctx->var->argv, my_env(ctx));
		perror(" execve");
		exit(126);
	}
	return (pid);
}

void	command(t_context *ctx)
{
	pid_t	pid;

	ctx->var->argv = ctx->ast->data.cmd.text;
	if (handle_builtin(ctx))
		return ;
	pid = help_func(ctx);
	if (pid < 0)
	{
		if(pid != -42)
			perror("fork");
		exit(1);
	}
	waitpid(pid, &ctx->var->stat, 0);
	if (WIFSIGNALED(ctx->var->stat))
	{
		if (WTERMSIG(ctx->var->stat) == SIGINT || WTERMSIG(ctx->var->stat) == SIGQUIT)
			write(1, "\n", 1);
		get_exit_status(WTERMSIG(ctx->var->stat) + 128, 0);
	}
	else
		get_exit_status(WEXITSTATUS(ctx->var->stat), 0);
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
		ctx->var->p = 1;
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
	ctx->var->fd[0] = dup(0);
	ctx->var->fd[1] = dup(1);
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
		ctx->var->input_fd = STDIN_FILENO;
		exec_ast_node(ctx, ctx->ast);
	}
	dup2(ctx->var->fd[0], 0);
	dup2(ctx->var->fd[1], 1);
	close(ctx->var->fd[0]);
	close(ctx->var->fd[1]);
	ctx->var->p = 0;
}
