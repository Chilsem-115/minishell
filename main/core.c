
#include "messh.h"
#include "execute.h"

char *ft_readline()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	char *prompt = ft_strjoin( "enigma@minishell:", cwd);
	prompt = ft_strjoin(prompt, "$ ");
	char *s = readline(prompt);
	if (!s)
	{
		printf("exit\n");
		exit(0);
	}

	free(prompt);
	if(s && *s)
		add_history(s);
	return (s);
}

static int	is_valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i++])
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (1);
	}
	return (0);
}

static void	handle_line(t_context *ctx)
{
	if (is_valid_line(ctx->line))
		add_history(ctx->line);
	ctx->tokens = tokenize(ctx->line);
	ctx->ast = generate_ast(ctx->tokens);
//	ctx->ast = expand_variables(ctx);
	// print_token_list(ctx->tokens);
	// ctx->tokens = NULL;
	// if (ctx->ast)
	// 	print_ast(ctx->ast);
	// else
	// 	printf("\n\n dafuq ? where is it\n");
	command_exec(ctx);
	ft_lstclear(&ctx->tokens, free);
	ast_clear(ctx->ast);
	ctx->ast = NULL;
} 

void	main_loop(t_context *ctx)
{
	while (1)
	{
		ctx->line = ft_readline();
		if (!ctx->line)
			break ;
		if (*ctx->line && ft_strncmp(ctx->line, "exit", 5) == 0)
			break ;
		if (*ctx->line)
			handle_line(ctx);
		free(ctx->line);
	}
}
