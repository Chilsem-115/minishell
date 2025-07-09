
#include "libft.h"

int	ft_isspace(int x)
{
	return (x == ' '  ||
			x == '\t' ||
			x == '\n' ||
			x == '\v' ||
			x == '\f' ||
			x == '\r');
}
