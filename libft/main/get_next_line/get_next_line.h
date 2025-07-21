/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 03:05:46 by itamsama          #+#    #+#             */
/*   Updated: 2025/05/21 00:04:17 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
int		handle_buffer(char **line, char *tmp, ssize_t read_val, char **remain);
int		handle_static(char **remain, char **line);
int		handle_tmp(char **remain, char *tmp, char **line);

#endif
