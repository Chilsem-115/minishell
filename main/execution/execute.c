
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
	str = ft_split(my_getenv("PATH", ctx->envp), ':');
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

	argv = ctx->ast->data.cmd.text;
	if (!ft_strncmp(argv[0], "cd", 3))
	{
		if(!argv[1])
			chdir("/home");
		else
			chdir(argv[1]);
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
			export_var(ctx->envp, argv[i]);
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

void	command_exec(t_context *ctx)
{
	pid_t	pid;
	char	*path;
	char	**argv;

	argv = ctx->ast->data.cmd.text;
	handle_builtin(ctx);
	pid = fork();
	if (pid == 0)
	{
		path = check_exec(argv[0], ctx);
		execve(path, argv, my_env(&ctx->envp));
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
}
