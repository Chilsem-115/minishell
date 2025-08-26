/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itamsama <itamsama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 04:35:54 by itamsama          #+#    #+#             */
/*   Updated: 2025/08/26 04:37:02 by itamsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "messh.h"

static int	env_key_eq(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strncmp(a, b, ft_strlen(a) + 1) == 0);
}

t_env	*env_find_node(t_env *head, const char *key)
{
	while (head)
	{
		if (env_key_eq(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}
