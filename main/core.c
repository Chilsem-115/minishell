
#include "messh.h"

static char	*trim_whitespace(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';

	return (str);
}

static char	*ft_readline()
{
//	char	cwd[1024];
	char	prompt[] = "messh> ";
	char	*s;

	/*
	getcwd(cwd, sizeof(cwd));
	prompt = ft_strjoin("", cwd);
	prompt = ft_strjoin(prompt, "$ ");
	*/
	s = readline(prompt);
	if (!s)
	{
		printf("exit\n");
		exit(0);
	}
//	free(prompt);
	if (s && *s)
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
	print_token_list(ctx->tokens);
	ctx->ast = generate_ast(ctx->tokens);
	ctx->tokens = NULL;
//	ctx->ast = expand_variables(ctx);
	if (ctx->ast)
		print_ast(ctx->ast);
	else
		printf("\n\n dafuq ? where is it\n");
//	execute_ast(ctx);
//	ft_lstclear(&ctx->tokens, free);
//	ast_clear(ctx->ast);
//	ctx->ast = NULL;
} 

void	main_loop(t_context *ctx)
{
	while (1)
	{
		ctx->line = ft_readline();
		if (!ctx->line)
			break ;
		ctx->line = trim_whitespace(ctx->line);
		if (*ctx->line && ft_strncmp(ctx->line, "exit", 5) == 0)
			break ;
		if (*ctx->line)
			handle_line(ctx);
		free(ctx->line);
	}
}
