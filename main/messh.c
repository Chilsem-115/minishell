/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:46:16 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/25 06:51:22 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "messh.h"

extern int	g_gsignum;

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
	g_gsignum = 2;
	rl_done = 1;
}

int	do_nothing(void)
{
	return (1);
}

static void	clear_all(t_context *ctx)
{
	free_env(ctx);
	if (ctx->var)
	{
		free(ctx->var->fd);
		free(ctx->var);
		ctx->var = NULL;
	}
	if (ctx->line)
	{
		free(ctx->line);
		ctx->line = NULL;
	}
	rl_clear_history();
}

static void	status_init(t_context *ctx, char **env)
{
	ctx->line = NULL;
	ctx->tokens = NULL;
	ctx->ast = NULL;
	ctx->errmsg = NULL;
	ctx->var = garbage_coll(0, sizeof(t_used_var));
	ctx->exit_code = 0;
	ctx->has_error = 0;
	ctx->var->max = 0;
	ctx->var->p = 0;
	ctx->envp = init_env(env);
	ctx->var->fd = garbage_coll(0, sizeof(int) * 2);
}

int	main(int argc, char **argv, char **env)
{
	t_context	ctx;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	rl_event_hook = do_nothing;
	saved_signal(signal(SIGINT, handler), signal(SIGQUIT, SIG_IGN), 0);
	status_init(&ctx, env);
	print_banner();
	main_loop(&ctx);
	clear_all(&ctx);
	return (0);
}
