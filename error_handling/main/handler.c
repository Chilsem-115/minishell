#include <stdlib.h>
#include <stdio.h>

void	handle_malloc(void *ctx)
{
	(void)ctx;
	fprintf(stderr, "Critical memory error. Exiting.\n");
	exit(EXIT_FAILURE);
}

void	handle_file(void *ctx)
{
	(void)ctx;
	fprintf(stderr, "Could not open file.\n");
}
