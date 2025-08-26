
#include "libft.h"

char	*deldup(char *str)
{
	char	buf[256];
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		while (k < j && buf[k] != str[i])
			k++;
		if (k == j)
			buf[j++] = str[i];
		i++;
	}
	buf[j] = '\0';
	ft_free(str);
	return (ft_strdup(buf));
}
