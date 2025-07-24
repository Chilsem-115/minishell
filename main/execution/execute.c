#include "../include/minishell.h"
#include "../Libft/libft.h"

char	**split_once(const char *str, char sep)
{
	char	**res = malloc(sizeof(char *) * 3);
	int		i = 0;

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

	return res;
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

char *check_exec(char *s, t_env *env_list)
{
	int    i;

	i = 0;
	char **str = ft_split(my_getenv("PATH", env_list), ':');
	if(!str)
		return(NULL);
	while(str[i])
	{
		char *path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, s);
		if(access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int handle_builtin(t_context *ctx)
{
	if (!ft_strncmp(args[0], "cd", 3))
	{
		if(!args[1] || ft_strncmp(args[1], "~", 2) == 0)
			chdir("/home/oessmiri");
		else
			chdir(args[1]);
	}
	else if (!ft_strncmp(args[0], "exit", 5))
		exit_command(args);
	else if (!ft_strncmp(args[0], "export", 7))
	{
		if (!args[1])
		{
			print_export(*env_list);
			return (1);
		}
		int i = 1;
		while(args[i])
		{
			export_var(env_list, args[i]);
			i++;
		}
	}
	else if (!ft_strncmp(args[0], "unset", 6) && args[1])
		unset_var(env_list, args[1]);
	else if (!ft_strncmp(args[0], "env", 4))
		print_env(*env_list);
	else if (!ft_strncmp(args[0], "pwd", 4))
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

	if (handle_builtin(t_context *ctx))
		continue ; // this will be later on used for error messages
	pid = fork();
	if (pid == 0)
	{
		path = check_exec(args[0], env_list);
		execve(path, args, my_env(&env_list));
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
		wait(NULL);
}
