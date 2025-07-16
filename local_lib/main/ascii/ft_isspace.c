
#include "libft.h"

int	ft_isspace(int x)
{
	if (x == ' ' || x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r')
		return (1);
	return (0);
}
