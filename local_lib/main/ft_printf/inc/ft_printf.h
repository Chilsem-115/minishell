/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.42.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 23:47:40 by itamsama          #+#    #+#             */
/*   Updated: 2024/12/22 16:44:56 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/* Character and string writers */
int		write_char(int fd, int c);
int		write_str(int fd, char *s);

/* Number writers */
int		write_nbr(int fd, int n);
int		write_unsigned(int fd, unsigned int n);

/* Hexadecimal and pointer writers */
int		write_hexa(int fd, unsigned long num, int uppercase); // 0 = lowercase, 1 = uppercase
int		write_ptr(int fd, void *ptr);

/* Core formatter */
int		format_string(int fd, const char *str, va_list args);

#endif
