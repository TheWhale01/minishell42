/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:24:10 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/15 11:25:19 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstdup(t_list *lst, void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*tmp_node;

	new = 0;
	tmp = lst;
	while (tmp)
	{
		tmp_node = ft_lstnew(tmp->content, sizeof(tmp->content));
		if (!tmp_node)
		{
			ft_lstclear(&new, del);
			return (0);
		}
		ft_lstadd_back(&new, tmp_node);
		tmp = tmp->next;
	}
	return (new);
}
