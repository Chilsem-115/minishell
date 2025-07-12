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

typedef struct	s_data
{
	char		*line;
	t_list		*tokens;
	//t_ast_node	*ast;
}	t_data;

void	status_init(t_data **status);
void	status_destroy(t_data *status);

#endif
