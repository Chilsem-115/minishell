#include "messh.h"
#include "libft.h"

static char *generate_heredoc_filename(void)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int fd = open("/dev/random", O_RDONLY);
    if (fd < 0)
        return NULL;

    char random_part[9];
    for (int i = 0; i < 8; i++) {
        unsigned char byte;
        if (read(fd, &byte, 1) != 1)
        {
            close(fd);
            return NULL;
        }
        random_part[i] = charset[byte % (sizeof(charset) - 1)];
    }
    random_part[8] = '\0';
    close(fd);
    char *filename = malloc(8 + 1);
    if (!filename)
        return NULL;

    strcpy(filename, random_part);

    return filename;
}


static char *generate_full_path(void)
{
    char *name = generate_heredoc_filename();
    if (!name)
        return NULL;

    char *full_path = malloc(strlen("/tmp/") + strlen(name) + 1);
    if (!full_path)
	{
        free(name);
        return NULL;
    }

    strcpy(full_path, "/tmp/");//..FORBIDEN
    strcat(full_path, name);//..FORBIDEN
    free(name);
    return (full_path);
}

void heredoc(t_ast_node *ast)
{
	int	fd_hd;
    char *s;
    char *full_path;

	full_path = generate_full_path();
	fd_hd = open(full_path, O_CREAT | O_RDWR | O_TRUNC, 0600);
	if (fd_hd < 0)
	{
    	perror("open heredoc");
    	free(full_path);
    	return;
	}
	s = readline("> ");
	while (s)
	{
		if (ft_strncmp(s, ast->data.redir.file, ft_strlen(s)) != 0)
        {
            write(fd_hd, s, ft_strlen(s));
	        s = readline("> ");
        }
        else
            exit(0);
	}
}
