/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:23:20 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/26 01:44:13 by oessmiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	*ft_malloc(t_list **garbage, size_t size)
{
	void	*p;
	t_list	*newnode;

	p = malloc(size);
	if (!p)
	{
		ft_lstclear(garbage, free);
		exit(1);
	}
	newnode = malloc(sizeof(t_list));
	if (!newnode)
	{
		free(p);
		ft_lstclear(garbage, free);
		exit(1);
	}
	newnode->next = NULL;
	newnode->content = p;
	ft_lstadd_back(garbage, newnode);
	return (p);
}

t_list	**gc_root(void)
{
	static t_list	*garbage;
	return (&garbage);
}

void	ft_free(void *addr)
{
	t_list *root;
	t_list *curr;
	t_list *parrent_node;

	root = *gc_root();
	curr = root;
	parrent_node = NULL;
	while (curr)
	{
		if (curr->content == addr)
		{
			if (parrent_node)
				parrent_node->next = curr->next;
			else
				root = curr->next;
			ft_lstdelone(curr, free);
			break ;
		}
		parrent_node = curr;
		curr = curr->next;
	}
	*gc_root() = root;
}

void	*garbage_coll(int f, size_t size)
{
	t_list	*garbage;
	void	*ret;

	garbage = *gc_root();
	if (f == 0)
	{
		ret = ft_malloc(&garbage, size);
		*gc_root() = garbage;
		return (ret);
		//return (ft_malloc(&garbage, size));
	}
	else if (f == 1)
	{
		ft_lstclear(&garbage, free);
		*gc_root() = garbage;
	}
	//*gc_root() = garbage;
	return (NULL);
}

void    ft_exit(int status)
{
    garbage_coll(1, -1);
    exit(status);
}
