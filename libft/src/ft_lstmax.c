/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:38:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/25 15:38:56 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmax(t_list *lst)
{
	t_list	*max;
	t_list	*tmp;

	max = NULL;
	tmp = lst;
	while (tmp)
	{
		if (!max || (*(int *)max->content < *(int *)tmp->content))
			max = tmp;
		tmp = tmp->next;
	}
	return (max);
}
