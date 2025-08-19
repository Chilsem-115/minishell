
#include "messh.h"
#include "execute.h"

char *ft_readline()
{
	char cwd[PATH_MAX];
	cwd[0] = 0;
	getcwd(cwd, sizeof(cwd));
	char *prompt = ft_strjoin( "enigma@minishell:", cwd);
	prompt = ft_strjoin(prompt, " $ ");
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

static int    is_valid_line(char *line)
{
    int    i;

    if (!line)
        return (0);
    i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return (1);
        i++;
    }
    return (0);
}

static void	handle_line(t_context *ctx)
{
	t_list *list;
	if (!is_valid_line(ctx->line))
		return ;
	add_history(ctx->line);
	ctx->tokens = tokenize(ctx->line);
	ctx->ast = generate_ast(ctx->tokens);

	// while (ctx->ast->data.redir.child != NULL)
	// {
	// 	printf("childptr: %p\n", ctx->ast->data.redir.child);
	// 	ctx->ast = ctx->ast->data.redir.child;
	// }

	// return ;
	// ctx->ast = expand_variables(ctx);
	//print_token_list(ctx->tokens);
	// ctx->tokens = NULL;
	// if (ctx->ast)
	// 	print_ast(ctx->ast);
	// else
	// 	printf("\n\n dafuq ? where is it\n");

	list = *get_heredocs();
	while (list)
	{
		if(heredoc(list->content) == false)
		{
			*get_heredocs() = NULL;
			return ;
		}
		list = list->next;
	}
	
	command_exec(ctx);
	ft_lstclear(&ctx->tokens, free);
	ast_clear(ctx->ast);
	*get_heredocs() = NULL;
	ctx->ast = NULL;
}

t_list	**get_heredocs()
{
	static t_list *heredocs;

	return (&heredocs);
}
void	main_loop(t_context *ctx)
{
	while (1)
	{
		ctx->line = ft_readline();
		if (!ctx->line)
			break ;
		// if (*ctx->line && ft_strncmp(ctx->line, "exit", 5) == 0)
		// 	break ;
		if (*ctx->line)
			handle_line(ctx);
		free(ctx->line);
	}
}
