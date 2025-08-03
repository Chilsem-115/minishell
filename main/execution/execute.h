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
#include "messh.h"


char	**split_once(const char *str, char sep);
void	ft_envadd_back(t_env **lst, t_env *new);
char	*check_exec(char *s, t_context *ctx);
char	*ft_readline();
char	**my_env(t_context *ctx);
char	*my_getenv(char *s, t_context *ctx);

void	command_exec(t_context *ctx);

/* environment initialization */
t_env	*init_env(char **envp);

// void	heredoc(t_token *t);

/* built-in handling*/
int		handle_builtin(t_context *ctx);

/* exports */
void	print_export(t_context *ctx);


/* mok */
void	print_env(t_env *env);

/* execute_utils*/
void    update_var(t_env **list, char *key, char *value);
t_env	*init_env(char **envp);
void	export_var(t_env **env_list, char *arg);
void	unset_var(t_env *env_list, char *key);
void	exit_command(char **args);
void	pwd();

//pipe
void pipline(t_context *ctx, t_ast_node *node, int input_fd);
void exec_ast_node(t_context *ctx, t_ast_node *node, int input_fd);

//redirections
void heredoc(t_ast_node *ast);
void redirections(t_ast_node *ast);

// #define GREEN "\33[0;32m"
// #define CYELL "\33[0;35m"
// #define RESET "\33[0;0m"

#endif
