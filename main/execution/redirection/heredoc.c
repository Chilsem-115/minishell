#include "messh.h"
#include "execute.h"
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
    char *filename = garbage_coll(0, 8 + 1);
    if (!filename)
        return NULL;
    strcpy(filename, random_part);
    return filename;
}

char *generate_full_path(void)
{
    char *name = generate_heredoc_filename();
    if (!name)
        return NULL;

    char *full_path = garbage_coll(0, strlen("/tmp/") + strlen(name) + 1);
    if (!full_path)
	{
        free(name);
        return NULL;
    }

    ft_strcpy(full_path, "/tmp/");
    strcat(full_path, name);//..FORBIDEN
    free(name);
    return (full_path);
}

int gsignum ;//?
bool    heredoc(char **list)
{
	int	fd_hd;
    char *s;
    char *file;

    file = generate_full_path();
    fd_hd = open(file, O_CREAT | O_RDWR | O_TRUNC , 0600);
    if (fd_hd < 0)
    {
        perror("open heredoc");
        free(file);
        return (false);
    }
    gsignum = 0;
    while (1)
    {
        gsignum = 0;
        s = readline("> ");
        if (s && ft_strncmp(s, *list, ft_strlen(s) + 1) != 0)
        {
            write(fd_hd, s, ft_strlen(s));
            write(fd_hd, "\n", 1);
        }
        else if (!gsignum)
        {
            close(fd_hd);
            break ;
        }
    }
    *list = file;
    return (true);
}
