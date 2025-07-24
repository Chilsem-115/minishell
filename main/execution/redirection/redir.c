#include "messh.h"
#include "ast.h"
#include "libft.h"

/*
static void red_in(t_token *t, int fd)
{
    fd = open(t->text, O_RDONLY);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
    dup2(fd, 1);
}

static void red_out(t_token *t, int fd)
{
    fd = open(t->text, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
	dup2(fd, 0);
}

static void red_append(t_token *t, int fd)
{
    fd = open(t->text, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
    {
        perror("open");
        close(fd);
    }
    dup2(fd, 0);
}

void redirections(t_token *t)
{
	int	fd;
	int	pid;

	while (t)
	{
		if (t->type == TOK_REDIR_IN)
			red_in(t, fd);
		else if (t->type == TOK_REDIR_OUT)
			red_out(t, fd);
		else if (t->type == TOK_REDIR_APPEND)
			red_append(t, fd);
		else if (t->type == TOK_HEREDOC)
        {
            pid = fork();
            if (pid == 0)
			    heredoc(t);
            else if(pid > 0)
                wait(NULL);
        }
        t = t->next;
    }
        
}
*/
