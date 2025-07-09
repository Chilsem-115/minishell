
#include "parser.h"

t_ast_node	*generate_ast(char *line, t_list *tokens)
{
	(void)line;
	if (!tokens)
		return (NULL);
	return (parse_expression(&tokens));
}
