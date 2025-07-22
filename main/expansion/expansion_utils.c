
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*str_replace_range(const char *src, size_t start, size_t len, const char *replacement)
{
	size_t	new_len;
	size_t	src_len;
	size_t	rep_len;
	char	*result;

	src_len = strlen(src);
	rep_len = strlen(replacement);
	new_len =  src_len - len + rep_len;
	result = malloc(new_len + 1);
	if (!result)
		return (NULL);
	memcpy(result, src, start);
	memcpy(result + start, replacement, rep_len);
	memcpy(result + start + rep_len, src + start + len, src_len - start - len);
	result[new_len] = '\0';
	return (result);
}


int	main(void)
{
	const char	*original = "Hello $USER!";
	const char	*replacement = "shadowman";

	// Replace "$USER" starting at index 6, length 5
	char	*result = str_replace_range(original, 6, 5, replacement);

	if (result)
	{
		printf("Original : %s\n", original);
		printf("Modified : %s\n", result);
		free(result);
	}
	else
	{
		fprintf(stderr, "Memory allocation failed\n");
	}

	return (0);
}
