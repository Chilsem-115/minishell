#include "execute.h"
#include "messh.h"

void left_cmd(t_context *ctx, t_ast_node *node, int input_fd, int *pipefd)
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
        exit(1);
}

void right(t_context *ctx, t_ast_node *node, int *pipefd)
{
    dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        exec_ast_node(ctx, node->data.ctrl.right, STDIN_FILENO);
        exit(1);
}

void pipline(t_context *ctx, t_ast_node *node, int input_fd)
{
    int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        exit(1);
    }
    left_pid = fork();
    if (left_pid == 0)
        left_cmd(ctx, node, input_fd, pipefd);

    right_pid = fork();
    if (right_pid == 0)
        right(ctx, node, pipefd);

    close(pipefd[0]);
    close(pipefd[1]);
    if (input_fd != STDIN_FILENO)
        close(input_fd);
    while (wait(NULL) > 0)
        ;
}
