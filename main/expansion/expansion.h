/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:35:32 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:35:48 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include "messh.h"
# include "tokenize.h"

/* ---------- types ---------- */
typedef enum e_emode
{
	EXP_NO = 0,
	EXP_UNQ,
	EXP_DQ
}		t_emode;

char	*expand_token_text(char *text, t_context *ctx);

/* parser */
t_env	*env_find_node(t_env *head, const char *key);
int		next_dollar(const char *s, int start, t_emode *out_mode); //!
int		grab_variable(const char *s, int pos, char **out_name);

/* utility functions */
char	*str_replace_range(const char *src, size_t start, size_t len,
			const char *replacement);
void	lst_replace_node(t_list **head, t_list *node, t_list *sub);
int		replace_one_at(char **expanded, int pos, t_context *ctx);

/* quote_strip */
void	strip_sentinels_post_expansion(t_list *tokens);
char	*remove_syntactic_sentinels(const char *s);
char	*remove_qouts(const char *s);
/* the main function */
void	expand_variables(t_context *ctx);

#endif
