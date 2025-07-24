/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:44:02 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/24 13:24:39 by itamsama         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenize.h"
# include "libft.h"
# include "ast_gen.h"

typedef struct s_context
{
	char			*line;
	t_list			*tokens;
	t_ast_node		*ast;
	char			*errmsg;
	unsigned int	has_error;
	int				exit_code;
	char			**envp;
}	t_context;

void	main_loop(t_context *ctx);

/* Preview functions */

void	print_token_list(t_list *tokens);
void	print_ast(t_ast_node *node);

#endif
