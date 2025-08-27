/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:37:31 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/27 01:33:04 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messh.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*str_replace_range(const char *src, size_t start, size_t len,
		const char *replacement)
{
	size_t	new_len;
	size_t	src_len;
	size_t	rep_len;
	char	*result;

	src_len = ft_strlen(src);
	rep_len = ft_strlen(replacement);
	new_len = src_len - len + rep_len;
	result = garbage_coll(0, new_len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, src, start);
	ft_memcpy(result + start, replacement, rep_len);
	ft_memcpy(result + start + rep_len, src + start + len, src_len - start - len);
	result[new_len] = '\0';
	return (result);
}

static t_list	*lst_find_prev(t_list *head, t_list *node)
{
	t_list	*prev;

	prev = NULL;
	while (head && head != node)
	{
		prev = head;
		head = head->next;
	}
	return (prev);
}

static t_list	*lst_remove_node(t_list **head, t_list *prev, t_list *node,
		void (*del)(void *))
{
	t_list	*next;

	if (!head || !*head || !node)
		return (NULL);
	next = node->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	if (del)
		del(node->content);
	ft_free(node);
	return (next);
}

static void	lst_splice_chain(t_list **head, t_list *prev, t_list *sub,
		t_list *next)
{
	t_list	*tail;

	if (!sub)
	{
		return ;
	}
	if (prev)
		prev->next = sub;
	else
		*head = sub;
	tail = ft_lstlast(sub);
	if (tail)
		tail->next = next;
}

/*
 * replace a single node with
 * a (possibly multi-node) chain; sub==NULL removes */
void	lst_replace_node(t_list **head, t_list *node, t_list *sub)
{
	t_list	*prev;
	t_list	*next;

	if (!head || !*head || !node)
		return ;
	prev = lst_find_prev(*head, node);
	if (prev == NULL && *head != node)
		return ;
	next = lst_remove_node(head, prev, node, free_token);
	lst_splice_chain(head, prev, sub, next);
}
