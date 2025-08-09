
#include "messh.h"
#include "libft.h"
#include "execute.h"

void pwd()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	cwd[ft_strlen(cwd)] = '\0';
	printf("%s\n", cwd);
}

void exit_command(char **args)
{
	// int status = get_exit_status();
	int status = 0;

	if(args[1])
		status = ft_atoi(args[1]);
	exit(status);
}

void  echo_cmd(t_context *ctx, char **argv)
{
	(void) ctx;
	int	i;
	int	j;
	int f;

	i = 1;
	f = 0;
	if (argv[i] && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] != 'n')
			{
				f = 0;
				i--;
				break;
			}
			f = 1;
			j++;
		}
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if(f == 0)
		printf("\n");
}

int lenlist(t_env *env_list)
{
	t_env *t;
	int	n;

	n = 0;
	t = env_list;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}