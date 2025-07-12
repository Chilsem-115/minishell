
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "messh.h"
#include "libft.h"

#include "libft.h"  // for t_list
#include <unistd.h>
#include <string.h>

const char	*token_type_str(t_tokentype type)
{
	if (type == TOK_WORD) return "TOK_WORD";
	if (type == TOK_SQUOTE) return "TOK_SQUOTE";
	if (type == TOK_DQUOTE) return "TOK_DQUOTE";
	if (type == TOK_PIPE) return "TOK_PIPE";
	if (type == TOK_REDIR_IN) return "TOK_REDIR_IN";
	if (type == TOK_HEREDOC) return "TOK_HEREDOC";
	if (type == TOK_REDIR_OUT) return "TOK_REDIR_OUT";
	if (type == TOK_REDIR_APPEND) return "TOK_REDIR_APPEND";
	if (type == TOK_ENV_VAR) return "TOK_ENV_VAR";
	if (type == TOK_EXIT_STATUS) return "TOK_EXIT_STATUS";
	return "TOK_UNKNOWN";
}

void	print_token_list(t_list *tokens, const char *line)
{
	t_token	*tok;

	while (tokens)
	{
		tok = (t_token *)tokens->content;

		const char *type_str = token_type_str(tok->type);
		write(STDOUT_FILENO, type_str, strlen(type_str));
		write(STDOUT_FILENO, ": ", 2);
		write(STDOUT_FILENO, &line[tok->start], tok->length);
		write(STDOUT_FILENO, "\n", 1);

		tokens = tokens->next;
	}
}

static void	print_banner(void)
{
	printf("\n");
	printf("\033[1;34m"); // Blue for border
	printf("  ╔══════════════════════════════════════════════╗\n");
	printf("  ║                                              ║\n");
	printf("  ║  \033[1;37m███╗   ███╗███████╗███████╗███████╗██╗  ██╗\033[1;34m ║\n");
	printf("  ║  \033[1;37m████╗ ████║██╔════╝██╔════╝██╔════╝██║  ██║\033[1;34m ║\n");
	printf("  ║  \033[1;37m██╔████╔██║█████╗  ███████╗███████╗███████║\033[1;34m ║\n");
	printf("  ║  \033[1;37m██║╚██╔╝██║██╔══╝  ╚════██║╚════██║██╔══██║\033[1;34m ║\n");
	printf("  ║  \033[1;37m██║ ╚═╝ ██║███████╗███████║███████║██║  ██║\033[1;34m ║\n");
	printf("  ║  \033[1;37m╚═╝     ╚═╝╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝\033[1;34m ║\n");
	printf("  ║                                              ║\n");
	printf("  ║       \033[0;37mMinimalist Experience Shell v0.1\033[1;34m       ║\n");
	printf("  ║                                              ║\n");
	printf("  ╚══════════════════════════════════════════════╝\n");
	printf("\033[0m\n");
	printf("\033[0;33m  ▶ \033[2;37mShell ready.\033[0m\n\n");
}

static char*	trim_whitespace(char *str)
{
	char	*end;

	while (isspace((unsigned char)*str))
		str++;
	if (*str == '\0')
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
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
	t_data	*status;

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
			print_token_list(status->tokens, status->line);
			/*
			ft_lstclear(&tokens, free);
			ast = generate_ast(status->line, status->tokens);
			print_ast(ast);
			*/
		}
		//free(status);
	}
	rl_clear_history();
	printf("Bye!\n");
	return (0);
}
