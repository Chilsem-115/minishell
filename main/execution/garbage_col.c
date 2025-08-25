/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessmiri <oessmiri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 23:23:20 by oessmiri          #+#    #+#             */
/*   Updated: 2025/08/25 06:25:04 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "messh.h"

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
	newnode = ft_lstnew(p);
	if (!newnode)
	{
		free(p);
		ft_lstclear(garbage, free);
		exit(1);
	}
	ft_lstadd_back(garbage, newnode);
	return (p);
}

void	*garbage_coll(int f, size_t size)
{
	static t_list	*garbage;

	if (f == 0)
		return (ft_malloc(&garbage, size));
	else if (f == 1)
		ft_lstclear(&garbage, free);
	return (NULL);
}
