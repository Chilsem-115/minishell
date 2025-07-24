#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

char	**split_once(const char *str, char sep);
void	ft_envadd_back(t_env **lst, t_env *new);
char	*check_exec(char *s, t_env *env_list);
int		handle_builtin(char **args, t_env **env_list);
char	*ft_readline();
void	handler(int sig);
void	exit_command(char **args);
t_env	*init_env(char **envp);
void	export_var(t_env **env_list, char *arg);
void	unset_var(t_env **env_list, char *key);
void	print_env(t_env *env);
void	pwd();
void	print_export(t_env *env);
char	**my_env(t_env **list_env);//?
char	*my_getenv(char *s, t_env *list);

// void	heredoc(t_token *t);

// #define GREEN "\33[0;32m"
// #define CYELL "\33[0;35m"
// #define RESET "\33[0;0m"

#endif
