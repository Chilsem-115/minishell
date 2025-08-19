#include <sys/types.h>
#include "messh.h"
#include "execute.h"
#include "libft.h"
#include <signal.h>

char **split_once(const char *str, char sep)
{
	char **res;
	int i;

	res = garbage_coll(0, sizeof(char *) * 3);
	i = 0;
	if (!res || !str)
		return NULL;
	while (str[i] && str[i] != sep)
		i++;
	res[0] = ft_substr(str, 0, i);
	if (str[i] == sep)
		res[1] = ft_strdup((char *)(str + i + 1));
	else
		res[1] = NULL;
	res[2] = NULL;
	return (res);
}

char *check_exec(char *s, t_context *ctx)
{
	int			i;
	char	**str;
	char	*path;

	i = 0;
	str = ft_split(my_getenv("PATH", ctx), ':');
	if (!str || !*str)
		return (s);
	while (str[i])
	{
		path = ft_strjoin(str[i], "/");
		path = ft_strjoin(path, s);
		if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		{
			perror("bash");
			exit(126);
		}
		else if(access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int exec_check(char *s)
{
	if (s[0] && (s[0] == '/' || (s[0] == '.' && s[1] == '/')))
		return (1);
	return (0);
}

void *saved_signal(void *sig1, void *sig2, int f)
{
	static void(*oldhdl_INT)(int);
	static void(*oldhdl_QUIT)(int);
	if (f == 0)
	{		
		oldhdl_INT = sig1;
		oldhdl_QUIT = sig2;
	}
	else if(f == 1)
		return (oldhdl_INT);
	return(oldhdl_QUIT);
}