/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:44:02 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/22 03:09:46 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSH_H
# define MESSH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "tokenize.h"
# include "ast_gen.h"

/* olive + reset (readline-safe) */
#define C_OLIVE "\001\033[38;5;142m\002"
#define C_RESET "\001\033[0m\002"

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_context
{
	char			*line;
	t_list			*tokens;
	t_ast_node		*ast;
	t_redir_node	heredocs;
	char			*errmsg;
	unsigned int	has_error;
	int				exit_code;
	//int				flag;
	int					max;
	int					p;
	int				stat;
	char			*path;
	char			**argv;
	t_env			*envp;
	int				*fd;
}	t_context;

void	main_loop(t_context *ctx);

/* Preview functions */


void	handler(int sig);
void	print_token_list(t_list *tokens);
void	print_ast(t_ast_node *node);

#endif
