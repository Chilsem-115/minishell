
#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dst;
	int		i;

	dst = (char *)malloc(n + 1);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

