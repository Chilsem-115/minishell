
#include <unistd.h>
#include "libft.h"
#include "tokenize.h"

void	err_unclosed_quote(void)
{
	const char	*msg;

	msg = "minishell: syntax error unclosed quote\n";
	write(2, msg, ft_strlen(msg));
}

void	err_unexpected_token(const char *tok)
{
	const char	*pre;
	const char	*post;

	pre = "minishell: syntax error near unexpected token `";
	post = "'\n";
	if (!tok || *tok == '\0')
		tok = "newline";
	write(2, pre, ft_strlen(pre));
	write(2, tok, ft_strlen(tok));
	write(2, post, ft_strlen(post));
}
