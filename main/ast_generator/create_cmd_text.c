
#include "tokenize.h"
#include "libft.h"

// Helper to count command-like tokens
static int	count_command_tokens(t_list *lst)
{
	int			count = 0;
	t_token		*tok;

	while (lst)
	{
		tok = (t_token *)lst->content;
		if (tok->type != TOK_WORD && tok->type != TOK_SQUOTE && tok->type != TOK_DQUOTE)
			break;
		count++;
		lst = lst->next;
	}
	return (count);
}

// Build an array of duplicated strings for command arguments
char	**gather_command_strings(t_list **cur, const char *line)
{
	int		count;
	char	**args;
	int		i = 0;
	t_token	*tok;

	count = count_command_tokens(*cur);
	if (count == 0)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (i < count && *cur)
	{
		tok = (t_token *)(*cur)->content;
		args[i] = dup_token_string(tok, line);
		if (!args[i])
		{
			// Free previously allocated strings
			while (--i >= 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
		i++;
		*cur = (*cur)->next;
	}
	args[i] = NULL;
	return (args);
}
