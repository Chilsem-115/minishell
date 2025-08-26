
#include "libft.h"
#include <stdio.h>

int main()
{
	int	*i = garbage_coll(ALLOC, sizeof(int));
	*i = 219398;
	printf("%d\n", *i);
//	ft_free(i);
	ft_exit(0);
	printf("wtf?");
}
