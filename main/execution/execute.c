
#include <sys/types.h>
#include "messh.h"
#include "execute.h"
#include "libft.h"

char	**split_once(const char *str, char sep)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * 3);
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

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env *node;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

char	*check_exec(char *s, t_context *ctx)
{
	int		i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split(my_getenv("PATH", ctx), ':');
	if(!str)
		return(NULL);
	while(str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, s);
		if(access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int	handle_builtin(t_context *ctx)
{
	char	**argv;
	int		i;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	argv = ctx->ast->data.cmd.text;
	if (!ft_strncmp(argv[0], "cd", 3))
	{
		if(!argv[1])
		{
			if(chdir(my_getenv("HOME", ctx)) == -1)
				printf("enigma: cd: HOME not set\n");
		}
		else
		{
			if(chdir(argv[1]) == -1)
				printf("cd: No such file or directory\n");
		}
		update_var(&ctx->envp, "OLDPWD", ft_strdup(cwd));
		update_var(&ctx->envp, "PWD", ft_strdup(getcwd(cwd, sizeof(cwd))));
	}
	else if (!ft_strncmp(argv[0], "exit", 5))
		exit_command(argv);
	else if (!ft_strncmp(argv[0], "export", 7))
	{
		if (!argv[1])
		{
			print_export(ctx);
			return (1);
		}
		i = 1;
		while(argv[i])
		{
			export_var(&ctx->envp, argv[i]);
			i++;
		}
	}
	else if (!ft_strncmp(argv[0], "unset", 6) && argv[1])
		unset_var(ctx->envp, argv[1]);
	else if (!ft_strncmp(argv[0], "env", 4))
		print_env(ctx->envp);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		pwd();
	// else if(!ft_strncmp(args[0], "echo", 5))// ??
	// 	// ??
	else
		return (0);
	return (1);
}

int exec_check(char *s)
{
	if (s[0] == '/' || (s[0] == '.' && s[1] == '/'))
		return (1);
	return (0);
}

void	command(t_context *ctx)
{
	pid_t	pid;
	char	*path;
	char	**argv;

	argv = ctx->ast->data.cmd.text;
	if (handle_builtin(ctx))
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (exec_check(argv[0]) == 1)
		{
			execve(argv[0], argv, my_env(ctx));
			printf("enigma: %s: No such file or directory\n", argv[0]);
			exit(127);
		}
		path = check_exec(argv[0], ctx);
		if(!path)
		{
			printf("enigma: %s: No such file or directory\n", argv[0]);
			exit(127);
		}
		execve(path, argv, my_env(ctx));
		perror("enigma : execve");
		exit(126);
	}
	else if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
	else if (pid > 0)
		 waitpid(pid, NULL, 0);
}

void exec_ast_node(t_context *ctx, t_ast_node *node, int input_fd)
{
	if (!node)
		return;

	if (node->type == AST_CONTROL && node->data.ctrl.op == CTRL_PIPE)
		pipline(ctx, node, input_fd);

	else if (node->type == AST_COMMAND)
	{
		ctx->ast = node;
		command(ctx);
	}
	else if (node->type == AST_REDIR)
		redirections(node);
}

void	command_exec(t_context *ctx)
{
	exec_ast_node(ctx, ctx->ast, STDIN_FILENO);
}