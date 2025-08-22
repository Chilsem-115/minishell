/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:33:23 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/22 03:32:46 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

void    left_cmd(t_context *ctx, t_ast_node *node, int input_fd, int *pipefd)
{
    if (input_fd != STDIN_FILENO)
	{
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    exec_ast_node(ctx, node->data.ctrl.left, STDIN_FILENO);
    close(0);
    close(1);
    exit(1);
}

void    right(t_context *ctx, t_ast_node *node, int *pipefd)
{
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);
    exec_ast_node(ctx, node->data.ctrl.right, STDIN_FILENO);
    close(0);
    close(1);
    exit(1);
}

static void	setup_signals(void (**oldhdl_INT)(int), void (**oldhdl_QUIT)(int))
{
	*oldhdl_INT = saved_signal(signal(SIGINT, SIG_IGN),
			signal(SIGQUIT, SIG_IGN), 1);
	*oldhdl_QUIT = saved_signal(signal(SIGINT, SIG_IGN),
			signal(SIGQUIT, SIG_IGN), 2);
}

static pid_t	launch_left(t_context *ctx, t_ast_node *node,
				int input_fd, int pipefd[2],
				void (*oldhdl_INT)(int), void (*oldhdl_QUIT)(int))
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(ctx->fd[0]);
		close(ctx->fd[1]);
		signal(SIGINT, oldhdl_INT);
		signal(SIGQUIT, oldhdl_QUIT);
		left_cmd(ctx, node, input_fd, pipefd);
	}
	return (pid);
}

static pid_t	launch_right(t_context *ctx, t_ast_node *node,
				int pipefd[2],
				void (*oldhdl_INT)(int), void (*oldhdl_QUIT)(int))
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(ctx->fd[0]);
		close(ctx->fd[1]);
		signal(SIGINT, oldhdl_INT);
		signal(SIGQUIT, oldhdl_QUIT);
		right(ctx, node, pipefd);
	}
	return (pid);
}

static void parent_wait(pid_t left_pid, pid_t right_pid, int stat1, int stat2)
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


void	pipline(t_context *ctx, t_ast_node *node, int input_fd)
{
	int		pipefd[2];
	int		stat1;
	int		stat2;
	pid_t	left_pid;
	pid_t	right_pid;
	void	(*oldhdl_INT)(int);
	void	(*oldhdl_QUIT)(int);

    stat1 = 0;
    stat2 = 0;
	setup_signals(&oldhdl_INT, &oldhdl_QUIT);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	left_pid = launch_left(ctx, node, input_fd, pipefd, oldhdl_INT, oldhdl_QUIT);
	right_pid = launch_right(ctx, node, pipefd, oldhdl_INT, oldhdl_QUIT);
	close(pipefd[0]);
	close(pipefd[1]);
	close(0);
	close(1);
	parent_wait(left_pid, right_pid, stat1, stat2);
}

char **check_empty(t_context *ctx)//--
{
	char **argv;

	argv = ctx->ast->data.cmd.text;
	if (!argv || !argv[0])
	{
	    ft_dprintf(2, "minishell: empty command\n");
	    exit(127);
	}
	return (argv);
}

void pipe_command(t_context *ctx)
{
	char	*path;
	char	**argv;

	argv = check_empty(ctx);//--
	if (handle_builtin(ctx))
		return ;
	if (exec_check(argv[0]) == 1)
	{
		execve(argv[0], argv, my_env(ctx));
		ft_dprintf(2, "%s: No such file or directory\n", argv[0]);
		exit(127);
	}
	path = check_exec(argv[0], ctx);
	if (!path)
	{
		ft_dprintf(2, "%s: command not found\n", argv[0]);
		exit(127);
	}
	execve(path, argv, my_env(ctx));
	perror("execve");
	exit(126);
}

// void    pipline(t_context *ctx, t_ast_node *node, int input_fd)
// {
//     int     pipefd[2];
//     int     stat1;
//     int     stat2;
//     pid_t   left_pid;
//     pid_t   right_pid;

//     static void(*oldhdl_INT)(int);
// 	static void(*oldhdl_QUIT)(int);

//     oldhdl_INT = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN), 1);
// 	oldhdl_QUIT = saved_signal(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN), 2);
//     if (pipe(pipefd) == -1)
// 	{
//         perror("pipe");
//         exit(1);
//     }
//     left_pid = fork();
//     if (left_pid == 0)
//     {
//         signal(SIGINT, oldhdl_INT);
//     	signal(SIGQUIT,oldhdl_QUIT);
//         left_cmd(ctx, node, input_fd, pipefd);
//     }

//     right_pid = fork();
//     if (right_pid == 0)
//     {
//         signal(SIGINT, oldhdl_INT);
//     	signal(SIGQUIT,oldhdl_QUIT);
//         right(ctx, node, pipefd);
//     }

//     close(pipefd[0]);
//     close(pipefd[1]);
//     close(0);
//     close(1);
//     waitpid(left_pid, &stat1, 0);
//     waitpid(right_pid, &stat2, 0);
// 	if (WIFSIGNALED(stat1) || WIFSIGNALED(stat2))
//     {
//         if (WTERMSIG(stat1) == SIGINT || WTERMSIG(stat1) == SIGQUIT || WTERMSIG(stat2) == SIGINT || WTERMSIG(stat2) == SIGQUIT)
//             write(2, "\n", 1);
//     }
// 	get_exit_status(stat2, 0);
//     signal(SIGINT, handler);
//     signal(SIGQUIT, SIG_IGN);
// }
