/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:02:40 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/24 04:28:35 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "messh.h"
# include "expansion.h"
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
#include <sys/stat.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int len(char **args);
int is_dir(const char *path);
char	**split_once(const char *str, char sep);
void	ft_envadd_back(t_env **lst, t_env *new);
char	*check_exec(char *s, t_context *ctx);
char	*ft_readline(void);
char	**my_env(t_context *ctx);
char	*my_getenv(char *s, t_context *ctx);
void    close_fds(t_context *ctx);
void	command_exec(t_context *ctx);
// exit status
long	get_exit_status(int st, int c);
void	unset_var(t_env **env_list, char *key);
/* built-in*/
t_env	*init_env(char **envp);
int		handle_builtin(t_context *ctx);
void	print_export(t_context *ctx);
void	print_env(t_env *env);
int		pwd(void);
void	echo_cmd(t_context *ctx, char **argv);
int		update_var(t_env **list, char *key, char *value, int k);
t_env	*init_env(char **envp);
void	export_var(t_env **env_list, char *arg);
// pipe
void	pipline(t_context *ctx);
void	setup_signals(void (**oldhdl_int)(int), void (**oldhdl_quit)(int));
void	right(t_context *ctx, int *pipefd);
void	left_cmd(t_context *ctx, int *pipefd);
void	pipe_command(t_context *ctx);
void	exec_ast_node(t_context *ctx, t_ast_node *node);
// redirections
t_list	**get_heredocs(void);
bool	heredoc(char **list, t_context *ctx);
int	redirections(t_ast_node *ast);
char	*generate_full_path(void);
int		lenlist(t_env *env_list);
int		exec_check(char *s);
// gcl
void	ast_clear(t_ast_node *ast);
void	*garbage_coll(int f, size_t size);
// signal
void	*saved_signal(void *sig1, void *sig2, int f);
// exit
long	long_atoi(char *s, t_context *ctx);
void	exit_command(t_context *ctx, char **args);
int		ft_strcmp(char *s1, char *s2);

#endif
