/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:45:47 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/25 15:46:16 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstindex(t_list *node, t_list *lst)
{
	int		index;
	t_list	*tmp;

	index = 0;
	tmp = lst;
	while (tmp)
	{
		if (*(int *)tmp->content == *(int *)node->content)
			return (index);
		index++;
		tmp = tmp->next;
	}
	return (-1);
}
