/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:32:32 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/09 15:28:39 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len(t_list **list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

char	*ft_first(t_list **list)
{
	t_list	*tmp;
	char	*min;

	tmp = *list;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (strcmp(min, tmp->content) > 0)
			min = tmp->content;
	}
	printf("%s\n", min);
	return (min);
}

char	*ft_min(char *str, t_list **list)
{
	t_list	*tmp;
	char	*min;

	tmp = *list;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
		if (strcmp(tmp->content, min) < 0 && strcmp(str, min) < 0)
			min = tmp->content;
	}
	return (min);
}

void	ft_list_sort(t_list **list)
{
	t_list	*tmp;
	char	*str;
	char	*min;
	int		i;

	i = -1;
	tmp = *list;
	min = ft_first(list);
	while (++i < ft_len(list))
	{
		tmp = *list;
		str = tmp->content;
		while (tmp->next)
		{
			tmp = tmp->next;
			if (strcmp(str, min) == 0)
				str = ft_min(min, list);
			else if (strcmp(tmp->content, str) < 0 && strcmp(min, tmp->content) < 0)
				str = tmp->content;
		}
		min = str;
		printf("%s\n", str);
	}
}

// }

// 	t_list	*tmp;
// 	char	*str;
// 	char	*min;
// 	int		i;

// 	i = -1;
// 	tmp = *list;
// 	min = NULL;
// 	while (++i < ft_len(list))
// 	{
// 		str = tmp->content;
// 		while (tmp && tmp->next)
// 		{
// 			tmp = tmp->next;
// 			if (ft_strcmp(str, tmp->content) > 0)
// 			{
// 				if (min)
// 				{
// 					if (ft_strcmp(str, min) > 0)
// 						str = tmp->content;
// 				}
// 				else
// 					str = tmp->content;
// 			}	
// 		}
// 		min = str;
// 		printf("%s\n", str);
// 	}

int	ft_export(t_list *list, char c)
{
	if (c == 's')
		ft_list_sort(&list);
	return (0);
}