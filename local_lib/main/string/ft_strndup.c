
#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dst;

	dst = (char *)malloc(n + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}

