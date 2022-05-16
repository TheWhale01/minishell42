/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 13:51:56 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/16 13:53:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsearch(t_list **lst, void *data, size_t size)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if (!ft_memcmp(tmp->content, data, size))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
