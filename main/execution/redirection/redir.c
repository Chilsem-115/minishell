#include "messh.h"
#include "ast.h"
#include "execute.h"
#include "libft.h"


static void red_in(t_ast_node *ast)
{
    int	fd;
    fd = open(ast->data.redir.file, O_RDONLY);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
    dup2(fd, 0);
}

static void red_out(t_ast_node *ast)
{
    int	fd;
    fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
	dup2(fd, 1);
}

static void red_append(t_ast_node *ast)
{
    int	fd;
    fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
    dup2(fd, 1);
}

void redirections(t_ast_node *ast)
{
	int	pid;

    if (!ast)
        return ;

    if (ast->type == AST_REDIR)
    {
        if (ast->data.redir.redir_type == REDIR_IN)
            red_in(ast);
	    else if (ast->data.redir.redir_type == REDIR_OUT)
            red_out(ast);
	    else if (ast->data.redir.redir_type == REDIR_APPEND)
            red_append(ast);
    }
    
	
	else if (ast->type == AST_REDIR && ast->data.redir.redir_type == REDIR_HEREDOC)
    {
        pid = fork();
        if (pid == 0)
		    heredoc(ast);
        else if(pid > 0)
            wait(NULL);
        else
            perror("pid");
    }
        redirections(ast->data.redir.child);
}
