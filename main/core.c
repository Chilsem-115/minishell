
#include "messh.h"

static void	handle_line(t_context *ctx)
{
	add_history(ctx->line);
	ctx->tokens = tokenize(ctx->line);
	print_token_list(ctx->tokens);
	ctx->ast = generate_ast(ctx->tokens);
	print_ast(ctx->ast);

	// future: expand_variables(ctx);
	// future: execute_ast(ctx);

	ft_lstclear(&ctx->tokens, free);
	ctx->tokens = NULL;
	ast_clear(ctx->ast); // if you implemented it
	ctx->ast = NULL;
} 

void	main_loop(t_data *status)
{
	while (1)
	{
		status->line = readline("messh> ");
		if (!status->line)
			break ;
		status->line = trim_whitespaces(status->line);
		if (*status->line && ft_strcmp(status->line, "exit") == 0)
			break ;
		if (*status->line)
			handle_line(status);
		free(status->line);
	}
}
