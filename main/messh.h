/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:44:02 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 07:48:08 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSH_H
# define MESSH_H

# include "ast_gen.h"
# include "libft.h"
# include "tokenize.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* olive + reset (readline-safe) */
# define C_OLIVE "\001\033[38;5;142m\002"
# define C_RESET "\001\033[0m\002"

typedef struct s_used_var
{
	int		max;
	int		p;
	int		stat;
	char	*path;
	char	**argv;
	int		stat1;
	int		stat2;
	int		*fd;
	int		input_fd;
}	t_used_var;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_context
{
	char			*line;
	t_list			*tokens;
	t_ast_node		*ast;
	int				exit_code;
	t_used_var		*var;
	t_env			*envp;
}					t_context;

void	main_loop(t_context *ctx);

/* Preview functions */
void	handler(int sig);
void	print_token_list(t_list *tokens);
void	print_ast(t_ast_node *node);

/* freeing allocation */
void	free_token(void *ptr);
void	free_env(t_context *ctx);
void	ast_clear(t_ast_node *ast);
void	ft_lstclear_gc(t_list **lst, void (*del)(void*));

#endif
