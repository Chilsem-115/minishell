
#ifndef ERR_HANDLER_H
#define ERR_HANDLER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

#define MAX_ERRORS 256

typedef enum e_error_code
{
	ERR_NONE,
	ERR_MALLOC,
	ERR_FILE,
	ERR_SYNTAX,
}	t_error_code;

typedef struct s_error
{
	t_error_code	code;
	const char		*message;
	void			(*handler)(void *context);
}	t_error;

void	report_error(t_error_code code, void *context);
void	register_error(t_error_code code, const char *msg, void (*handler)(void *));

#endif
