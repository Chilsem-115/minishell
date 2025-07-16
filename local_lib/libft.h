/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:37:49 by itamsama          #+#    #+#             */
/*   Updated: 2024/11/15 10:00:34 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* standard library finctions */
void	ft_bzero(void *str, size_t b);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t count);
void	*ft_calloc(size_t num, size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, unsigned int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_tolower(int x);
int		ft_toupper(int x);
int		ft_isalpha(int x);
int		ft_isdigit(int x);
int		ft_isascii(int x);
int		ft_isprint(int x);
int		ft_isalnum(int x);
int		ft_isspace(int x);
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t count);
int		ft_atoi(char *str);
char	*ft_strrchr(const char *str, int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strnstr(const char *big, const char *lil, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *src, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* linked list creation and manipulation */
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* file reading */
char	*get_next_line(int fd);
void	read_file(int fd, char **buffer);

/* printf variations */
int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);

#endif
