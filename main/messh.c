/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:46:16 by itamsama          #+#    #+#             */
/*   Updated: 2025/07/20 22:49:19 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "messh.h"
#include "libft.h"
#include "ast_gen.h"

const char	*token_type_str(t_tokentype type)
{
	if (type == TOK_WORD)
		return "TOK_WORD";
	if (type == TOK_SQUOTE)
		return "TOK_SQUOTE";
	if (type == TOK_DQUOTE)
		return "TOK_DQUOTE";
	if (type == TOK_PIPE)
		return "TOK_PIPE";
	if (type == TOK_REDIR_IN)
		return "TOK_REDIR_IN";
	if (type == TOK_HEREDOC)
		return "TOK_HEREDOC";
	if (type == TOK_REDIR_OUT)
		return "TOK_REDIR_OUT";
	if (type == TOK_REDIR_APPEND)
		return "TOK_REDIR_APPEND";
	if (type == TOK_ENV_VAR)
		return "TOK_ENV_VAR";
	return "TOK_UNKNOWN";
}

void	print_token_list(t_list *tokens)
{
	t_token	*tok;
	const char *type_str;

	while (tokens)
	{
		tok = (t_token *)tokens->content;
		type_str = token_type_str(tok->type);

		write(STDOUT_FILENO, type_str, strlen(type_str));
		write(STDOUT_FILENO, ": ", 2);
		if (tok->text)
			write(STDOUT_FILENO, tok->text, strlen(tok->text));
		else
			write(STDOUT_FILENO, "(none)", 6);
		write(STDOUT_FILENO, "\n", 1);

		tokens = tokens->next;
	}
}

static void	print_banner(void)
{
	printf("\n"
	"\033[1;34m" // Blue for border
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

void	status_init(t_data **status)
{
	*status = malloc(sizeof(t_data));
	if (!*status)
		return ;
	(*status)->line = NULL;
	(*status)->tokens = NULL;
}

int	main(void)
{
	t_data		*status;
	t_ast_node	*ast = NULL;

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
			ast = generate_ast(status->tokens);
			print_ast(ast);
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
