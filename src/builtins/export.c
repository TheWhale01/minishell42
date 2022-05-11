/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/11 16:24:16 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (ft_strncmp(str, "export", 6) != 0)
		return (1);
	str += 6;
	while (*str == ' ')
		str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	if (!*str)
		return (1);
	str++;
	while (*str && *str != ' ')
		str++;
	while (*str)
	{
		if (!ft_isalpha(*str) && *str != ' ')
			return (1);
		str++;
	}
	return (0);
}

int	ft_export(t_list *list, char *str)
{
	if (ft_strcmp(str, "export") == 0)
		ft_list_sort(&list);
	if (ft_verif(str))
	{
		printf("error\n");
		return (1);
	}
	else
		printf("VALIDE\n");
	return (0);
}
