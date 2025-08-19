
#include "messh.h"
#include "libft.h"
#include "execute.h"

void pwd()
{
	char cwd[PATH_MAX];
	if(!getcwd(cwd, sizeof(cwd)))
	{
		printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return ;
	}
	else
	{
		cwd[ft_strlen(cwd)] = '\0';
		printf("%s\n", cwd);
	}
	// else
	// {
	// 	ft_strjoin
	// 	printf("%s\n", getcwd(cwd, sizeof(cwd)));
	// }
}

long long_atoi(char *s, t_context *ctx)
{
    int i;
    long j;
    int r;
	int digit;

	i = 0;
	j = 0;
	r = 1;
    while (s[i] && ((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
        i++;
    if (s[i] == '-' || s[i] == '+')
	{
        if (s[i] == '-')
            r = -1;
        i++;
    }
    while (s[i] >= '0' && s[i] <= '9')
	{
        digit = s[i] - '0';

        if (r == 1 && (j > (LLONG_MAX - digit) / 10)) {
            ctx->max = 1;
            return 0;
        }
        if (r == -1 && (-j < (LLONG_MIN + digit) / 10)) {
            ctx->max = 1;
            return 0;
        }
        j = j * 10 + digit;
        i++;
    }
    return j * r;
}

int number_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

void exit_command(t_context	*ctx, char **args)
{
	long status = get_exit_status(0, 1);

	if(ctx->p != 1)
		printf("exit\n");
	if(args[1])
	{
		status = long_atoi(args[1], ctx);
		if(ctx->max == 1 || number_check(args[1]) == 1)
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
	}
	if(args[2])
		printf("bash: exit: too many arguments\n");
	else
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

long get_exit_status(int st, int c)
{
	static long status;
	if (c == 0)
		status = st;
	return (status);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
