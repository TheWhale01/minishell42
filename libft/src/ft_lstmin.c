/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:55:13 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/25 15:57:58 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmin(t_list *lst)
{
	t_list	*min;
	t_list	*tmp;

	min = lst;
	tmp = lst;
	while (tmp)
	{
		if (*(int *)tmp->content < *(int *)min->content)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}
