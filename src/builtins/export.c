/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:32:32 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/11 13:41:53 by jrossett         ###   ########.fr       */
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

void	ft_put_export(char *str)
{
	int	i;

	i = 0;
	ft_putstr("declare -x ");
	while (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		ft_putchar(str[i++]);
	ft_putchar(str[i++]);
	ft_putchar('\"');
	while (str[i])
		ft_putchar(str[i++]);
	ft_putstr("\"\n");
}

void	ft_list_sort(t_list **list)
{
	t_list	*tmp;
	char	*str;
	char	*min;
	int		i;

	i = 0;
	tmp = *list;
	min = "\0";
	str = "~";
	while (++i < ft_len(list))
	{
		tmp = *list;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->content, str) < 0
				&& ft_strcmp(tmp->content, min) > 0)
				str = tmp->content;
			tmp = tmp->next;
		}
		min = str;
		ft_put_export(str);
		str = "~";
	}
}

int	ft_export(t_list *list, char c)
{
	if (c == 's')
		ft_list_sort(&list);
	return (0);
}
