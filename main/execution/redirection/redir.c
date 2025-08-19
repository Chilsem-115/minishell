#include "messh.h"
#include "ast.h"
#include "execute.h"
#include "libft.h"

void red_in(t_ast_node *ast)
{
    int	fd;

    fd = open(ast->data.redir.file, O_RDONLY);
	if (fd == -1)
    {
        perror("-->open");
        return ;
    }
    if(dup2(fd, 0) == -1)
        perror("dup2");
    close(fd);
}

static void red_out(t_ast_node *ast)
{
    int	fd;

    fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
    {
        perror("open");
        return ;
    }
    if(dup2(fd, 1) == -1)
        perror("dup2");
    close(fd);
}

static void red_append(t_ast_node *ast)
{
    int	fd;

    fd = open(ast->data.redir.file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
    {
        perror("open");
        return ;
    }
    if(dup2(fd, 1) == -1)
        perror("dup2");
    close(fd);
}

void redirections(t_ast_node *ast)
{
    char    *full_file;
    int     a;

    a = dup(0);
    if (!ast)
        return ;
    redirections(ast->data.redir.child);
    if (ast->type == AST_REDIR)
    {
        if (ast->data.redir.redir_type == REDIR_IN || ast->data.redir.redir_type == REDIR_HEREDOC)
            red_in(ast);
	    else if (ast->data.redir.redir_type == REDIR_OUT)
            red_out(ast);
	    else if (ast->data.redir.redir_type == REDIR_APPEND)
            red_append(ast);
    }
}
