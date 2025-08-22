#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "messh.h"
#include <linux/limits.h>

char	**split_once(const char *str, char sep);
void	ft_envadd_back(t_env **lst, t_env *new);
char	*check_exec(char *s, t_context *ctx);
char	*ft_readline();
char	**my_env(t_context *ctx);
char	*my_getenv(char *s, t_context *ctx);

void	command_exec(t_context *ctx);

// void	heredoc(t_token *t);


// exit status
long get_exit_status(int st, int c);

void	unset_var(t_env **env_list, char *key);
/* built-in*/

t_env	*init_env(char **envp);
int		handle_builtin(t_context *ctx);
void	print_export(t_context *ctx);
void	print_env(t_env *env);
int    pwd();
void  echo_cmd(t_context *ctx, char **argv);
int    update_var(t_env **list, char *key, char *value, int k);
t_env	*init_env(char **envp);
void	export_var(t_env **env_list, char *arg);

//pipe
void pipline(t_context *ctx, t_ast_node *node, int input_fd);
void pipe_command(t_context *ctx);
void exec_ast_node(t_context *ctx, t_ast_node *node, int input_fd);

//redirections
t_list	**get_heredocs();
void red_in(t_ast_node *ast);
bool heredoc(char **list);
void redirections(t_ast_node *ast);
char *generate_full_path(void);

int lenlist(t_env *env_list);
int exec_check(char *s);

//gcl
void    ast_clear(t_ast_node *ast);
void    *garbage_coll(int f,  size_t size);

//signal
void *saved_signal(void *sig1, void *sig2, int f);

//exit
long	long_atoi(char *s, t_context *ctx);
void	exit_command(t_context *ctx, char **args);


int		ft_strcmp(char *s1, char *s2);
// #define GREEN "\33[0;32m"
// #define CYELL "\33[0;35m"
// #define RESET "\33[0;0m"

#endif
