/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:19:34 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/25 04:24:48 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "expansion.h"
#include "messh.h"

extern int	g_gsignum;
char	*ft_readline(void)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*prompt;
	char	*s;

	cwd[0] = 0;
	getcwd(cwd, sizeof(cwd));
	tmp = ft_strjoin(C_OLIVE "enigma@minishell:", cwd);
	prompt = ft_strjoin(tmp, C_RESET "$ ");
	free(tmp);
	while (1)
	{
		g_gsignum = 0;
		s = readline(prompt);
		if (!s)
		{
			free(s);
			ft_dprintf(2, "exit\n");
			exit(get_exit_status(0, 1));
		}
		if (g_gsignum == 2)
		{
			free(s);
			continue ;
		}
		if (s && *s)
			add_history(s);
		break ;
	}
	free(prompt);
	return (s);
}

/*
char	*ft_readline(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*s;

	cwd[0] = 0;
	getcwd(cwd, sizeof(cwd));
	prompt = ft_strjoin( "enigma@minishell:", cwd);
	prompt = ft_strjoin(prompt, "$ ");
	s = readline(prompt);
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
*/

static int	is_valid_line(char *line)
{
	int	i;

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
	//t_list	*list;

	if (!is_valid_line(ctx->line))
		return ;
	ctx->tokens = tokenize(ctx->line);
	expand_variables(ctx);
	ctx->ast = generate_ast(ctx->tokens);
	  print_token_list(ctx->tokens);
	  print_ast(ctx->ast);
	  /*
	list = *get_heredocs();
	while (list)
	{
		if (heredoc(list->content, ctx) == false)
		{
			*get_heredocs() = NULL;
			return ;
		}
		list = list->next;
	}
	command_exec(ctx);
	*/
	ft_lstclear(&ctx->tokens, free);
	ast_clear(ctx->ast);
	*get_heredocs() = NULL;
	ctx->ast = NULL;
}

t_list	**get_heredocs(void)
{
	static t_list	*heredocs;

	return (&heredocs);
}
void	main_loop(t_context *ctx)
{
	while (1)
	{
		ctx->line = ft_readline();
		// if (*ctx->line && ft_strncmp(ctx->line, "exit", 5) == 0)
		// 	break ;
		if (!ctx->line)
			exit(get_exit_status(0, 1));
		if (*ctx->line) // check later why
			handle_line(ctx);
		garbage_coll(1, 0);
		free(ctx->line);
	}
}
