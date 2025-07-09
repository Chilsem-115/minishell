
#include "ft_printf.h"

static void	cases(char chr, va_list args, int *count, int fd)
{
	if (chr == 'c')
		*count += write_char(fd, va_arg(args, int));
	else if (chr == 's')
		*count += write_str(fd, va_arg(args, char *));
	else if (chr == 'p')
		*count += write_ptr(fd, va_arg(args, void *));
	else if (chr == 'd' || chr == 'i')
		*count += write_nbr(fd, va_arg(args, int));
	else if (chr == 'u')
		*count += write_unsigned(fd, va_arg(args, unsigned int));
	else if (chr == 'x')
		*count += write_hexa(fd, va_arg(args, unsigned int), 0);
	else if (chr == 'X')
		*count += write_hexa(fd, va_arg(args, unsigned int), 1);
	else if (chr == '%')
		*count += write_char(fd, '%');
}

int	format_string(int fd, const char *str, va_list args)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			cases(*str, args, &count, fd);
		}
		else
			count += write_char(fd, *str);
		str++;
	}
	return (count);
}

