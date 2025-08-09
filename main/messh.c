/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:46:16 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/24 22:33:15 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"
#include "execute.h"

/*
static char*	trim_whitespace(char *str)
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

int	main(void)
{
	t_data		*status;

	status_init(&status);
	print_banner();
	while (1)
	{
		status->line = readline("mesh> ");
		if (status->line == NULL)
			break ;
		status->line = trim_whitespace(status->line);
		if (*status->line && strcmp(status->line, "exit") == 0)
		{
			free(status->line);
			break;
		}
		if (*status->line)
		{
			add_history(status->line);
			status->tokens = tokenize(status->line);
			print_token_list(status->tokens);
			status->ast = generate_ast(status->tokens);
			printf("\n\n\n\n");
			print_ast(status->ast);
			ft_lstclear(&status->tokens, free); // corrected
			//eree_ast(ast); // optional, if implemented
		}
		free(status->line);
	}
	free(status);
	rl_clear_history();
	printf("Bye!\n");
	return (0);
}
*/
////////////////////// stuff here ain't it

static void	print_banner(void)
{
	printf("\n"
	"\033[1;34m"
	"  ╔══════════════════════════════════════════════╗\n"
	"  ║                                              ║\n"
	"  ║  \033[1;37m███╗   ███╗███████╗███████╗███████╗██╗  ██╗\033[1;34m ║\n"
	"  ║  \033[1;37m████╗ ████║██╔════╝██╔════╝██╔════╝██║  ██║\033[1;34m ║\n"
	"  ║  \033[1;37m██╔████╔██║█████╗  ███████╗███████╗███████║\033[1;34m ║\n"
	"  ║  \033[1;37m██║╚██╔╝██║██╔══╝  ╚════██║╚════██║██╔══██║\033[1;34m ║\n"
	"  ║  \033[1;37m██║ ╚═╝ ██║███████╗███████║███████║██║  ██║\033[1;34m ║\n"
	"  ║  \033[1;37m╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝\033[1;34m ║\n"
	"  ║                                              ║\n"
	"  ║       \033[0;37mMinimalist Experience Shell v0.1\033[1;34m       ║\n"
	"  ║                                              ║\n"
	"  ╚══════════════════════════════════════════════╝\n"
	"\033[0m\n"
	"\033[0;33m  ▶ \033[2;37mShell ready.\033[0m\n\n");
}

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

static void	clean_exit(t_context *ctx)
{
	if (ctx->line)
		free(ctx->line);
	if (ctx->tokens)
		ft_lstclear(&ctx->tokens, free);
	/*
	if (ctx->ast)
		ast_clear(ctx->ast);
		*/
	if (ctx->errmsg)
		free(ctx->errmsg);
	free(ctx);
	rl_clear_history();
	printf("Bye!\n");
	exit(0);
}

static void	status_init(t_context *ctx, char **env)
{
	ctx->line = NULL;
	ctx->tokens = NULL;
	ctx->ast = NULL;
	ctx->errmsg = NULL;
	ctx->exit_code = 0;
	ctx->has_error = 0;
	ctx->envp = init_env(env);
}

int	main(int argc, char **argv, char **env)
{
	t_context	*ctx;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	ctx = malloc(sizeof(t_context));
	if (!ctx)
		return (1);
	status_init(ctx, env);
	print_banner();
	main_loop(ctx);
	clean_exit(ctx);
	return (0);
}
