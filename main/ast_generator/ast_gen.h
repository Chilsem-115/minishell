/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_gen.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:52:03 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 05:00:31 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_GEN_H
# define AST_GEN_H

# include "ast.h"
# include "libft.h"
# include "tokenize.h"
# include <stdlib.h>

/* Entry point (requires tokens) */
t_ast_node	*generate_ast(t_list *tokens);

#endif
