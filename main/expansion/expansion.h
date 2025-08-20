
#ifndef	EXPANSION_H
#define EXPANSION_H

# include "messh.h"
# include "tokenize.h"
# include "libft.h"

/* ---------- types ---------- */
typedef enum e_emode
{
	EXP_NO = 0,
	EXP_UNQ,
	EXP_DQ
}	t_emode;

/* parser */
t_env	*env_find_node(t_env *head, const char *key);
int		next_dollar(const char *s, int start, t_emode *out_mode);
int		grab_variable(const char *s, int pos, char **out_name);

/* utility functions */
char	*str_replace_range(const char *src, size_t start, size_t len, const char *replacement);
void	lst_replace_node(t_list **head, t_list *node, t_list *sub);


/* the main function */
void	expand_variables(t_context *ctx);

#endif
