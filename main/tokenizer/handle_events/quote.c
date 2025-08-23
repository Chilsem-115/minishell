
#include "tokenize.h"

int	quote_handler(t_tokenizer_state *ctx, char *line)
{
	size_t	start;
	size_t	i;
	char	*word;

	if (line[ctx->pos] != '\'' && line[ctx->pos] != '"')
		return (0);
	start = ctx->pos;
	i = ctx->pos;
	i += skip_quoted(ctx, line, i);
	while (line[i] && !isspace((unsigned char)line[i]) && !is_op_char(line[i]))
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			size_t	cons = skip_quoted(ctx, line, i);
			i += cons;
			continue ;
		}
		i++;
	}
	word = ft_strndup(&line[start], i - start);
	if (!word)
		tokenizer_error(ERR_MEMORY);
	create_token(ctx, word, TOK_WORD);
	ctx->pos = i;
	return (1);
}
