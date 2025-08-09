
#include <sys/types.h>
#include "messh.h"
#include "execute.h"
#include "libft.h"

char **split_once(const char *str, char sep)
{
	char **res;
	int i;

	res = garbage_coll(0, sizeof(char *) * 3);
	i = 0;
	if (!res || !str)
		return NULL;
	while (str[i] && str[i] != sep)
		i++;
	res[0] = ft_substr(str, 0, i);
	if (str[i] == sep)
		res[1] = ft_strdup((char *)(str + i + 1));
	else
		res[1] = NULL;
	res[2] = NULL;
	return (res);
}

char *check_exec(char *s, t_context *ctx)
{
	int			i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split(my_getenv("PATH", ctx), ':');
	if (!str || !*str)
		return (s);
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, s);
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		{
			perror("bash");
			exit(126);
		}
		else if(access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int exec_check(char *s)
{
	if (s[0] == '/' || (s[0] == '.' && s[1] == '/'))
		return (1);
	return (0);
}

void command(t_context *ctx)
{
	int	stat;
	pid_t	pid;
	char	*path;
	char	**argv;

	if (ctx->ast->data.cmd.text)
		argv = ctx->ast->data.cmd.text;
	else
		argv = NULL;
	if (handle_builtin(ctx))
		return;
	signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
    	signal(SIGQUIT, SIG_DFL);
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
		perror(" execve");
		exit(126);
	}
	else if (pid < 0)
	{
	    perror("fork");
	    exit(1);
	}
    waitpid(pid, &stat, 0);
	if (WIFSIGNALED(stat))
    {
        if (WTERMSIG(stat) == SIGINT || WTERMSIG(stat) == SIGQUIT)
            write(1, "\n", 1);
    }
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
}

void exec_ast_node(t_context *ctx, t_ast_node *node, int input_fd)
{
	if (!node){
		// ft_dprintf(2, "invalid '|' or redir ... \n");
		return;
	}
	if (node->type == AST_CONTROL && node->data.ctrl.op == CTRL_PIPE)
		pipline(ctx, node, input_fd);

	else if (node->type == AST_COMMAND)
	{
		ctx->ast = node;
		pipe_command(ctx);
	}
}

void command_exec(t_context *ctx)
{
	int fd[2];

	if (ctx->ast->type == AST_COMMAND)
	{
		command(ctx);
		return ;
	}
	else if (ctx->ast->type == AST_REDIR)
	{
		redirections(ctx->ast);
		return ;
	}
	fd[0] = dup(0);
	fd[1] = dup(1);
	exec_ast_node(ctx, ctx->ast, STDIN_FILENO);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
