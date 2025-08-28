/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:33:23 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/27 22:23:36 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

static pid_t	launch_left(t_context *ctx, int pipefd[2],
		void (*oldhdl_int)(int), void (*oldhdl_quit)(int))
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// close(ctx->var->fd[0]);
		close(ctx->var->fd[1]);
		signal(SIGINT, oldhdl_int);
		signal(SIGQUIT, oldhdl_quit);
		left_cmd(ctx, pipefd);
	}
	return (pid);
}

static pid_t	launch_right(t_context *ctx, int pipefd[2],
		void (*oldhdl_int)(int), void (*oldhdl_quit)(int))
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, oldhdl_int);
		signal(SIGQUIT, oldhdl_quit);
		right(ctx, pipefd);
		close(ctx->var->fd[0]);
		// close(ctx->var->fd[1]);
	}
	return (pid);
}

static void	parent_wait(pid_t left_pid, pid_t right_pid, int stat1, int stat2)
{
	waitpid(left_pid, &stat1, 0);
	waitpid(right_pid, &stat2, 0);
	if (WIFSIGNALED(stat2))
	{
		if (WTERMSIG(stat2) == SIGINT || WTERMSIG(stat2) == SIGQUIT)
			write(2, "\n", 1);
		get_exit_status(WTERMSIG(stat2) + 128, 0);
	}
	else if (WIFSIGNALED(stat1))
	{
		if (WTERMSIG(stat1) == SIGINT || WTERMSIG(stat1) == SIGQUIT)
			write(2, "\n", 1);
		get_exit_status(WTERMSIG(stat1) + 128, 0);
	}
	else
		get_exit_status(WEXITSTATUS(stat2), 0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	pipline(t_context *ctx)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	void	(*oldhdl_int)(int);
	void	(*oldhdl_quit)(int);

	ctx->var->stat1 = 0;
	ctx->var->stat2 = 0;
	setup_signals(&oldhdl_int, &oldhdl_quit);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_exit(1);
	}
	left_pid = launch_left(ctx, pipefd, oldhdl_int, oldhdl_quit);
	right_pid = launch_right(ctx, pipefd, oldhdl_int, oldhdl_quit);
	close(pipefd[0]);
	close(pipefd[1]);
	close(0);
	close(1);
	parent_wait(left_pid, right_pid, ctx->var->stat1, ctx->var->stat2);
}

void	pipe_command(t_context *ctx)
{
	char	*path;
	char	**argv;

	if (!ctx->ast->data.cmd.text || !ctx->ast->data.cmd.text[0])
		return ;
	argv = ctx->ast->data.cmd.text;
	if (handle_builtin(ctx))
		return ;
	if (exec_check(argv[0]) == 1)
	{
		execve(argv[0], argv, my_env(ctx));
		ft_dprintf(2, "%s: No such file or directory\n", argv[0]);
		ft_exit(127);
	}
	path = check_exec(argv[0], ctx);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", argv[0]);
		ft_exit(127);
	}
	execve(path, argv, my_env(ctx));
	perror("execve");
	ft_exit(126);
}
