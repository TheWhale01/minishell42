/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:18:09 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/11 16:22:00 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsearch(t_list *lst, void *data, size_t size)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_memcmp(lst->content, data, size))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
