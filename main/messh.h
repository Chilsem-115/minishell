/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:44:02 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:44:22 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSH_H
# define MESSH_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenize.h"
# include "libft.h"
# include "ast.h"
# include "ast_gen.h"

typedef struct s_data
{
	char		*line;
	t_list		*tokens;
	//t_ast_node	*ast;
}	t_data;

void	status_init(t_data **status);
void	status_destroy(t_data *status);
void	print_ast(t_ast_node *node);

#endif
