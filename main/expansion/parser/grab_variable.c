#include "libft.h"
#include <stddef.h>

static int	is_name_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static int	is_name_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	grab_variable(const char *s, int pos, char **out_name)
{
	int	start;
	int	i;

	*out_name = NULL;
	if (!s || s[pos] != '$' || !s[pos + 1])
		return (0);
	if (!is_name_start(s[pos + 1]))
		return (0);
	start = pos + 1;
	i = start;
	while (s[i] && is_name_char(s[i]))
		i++;
	*out_name = ft_substr(s, start, (size_t)(i - start));
	if (!*out_name)
		return (-1);
	return (i - pos);
}
