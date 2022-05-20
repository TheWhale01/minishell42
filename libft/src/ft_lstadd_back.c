/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:26:49 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/18 15:48:44 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **list, t_list *tmp)
{
	t_list	*end;

	if (!list)
		return ;
	if (!(*list))
	{
		*list = tmp;
		return ;
	}
	end = *list;
	while (end->next)
		end = end->next;
	end->next = tmp;
}
