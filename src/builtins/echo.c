/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:55:11 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/30 19:00:51 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_option(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo(t_data *data, char **arg)
{
	int		i;
	int		var;

	(void) data;
	var = 0;
	if (ft_len_double(arg) == 1)
		return (printf("\n"), 0);
	i = 1;
	while (arg[i] && ft_option(arg[i]))
	{
		var = 1;
		i++;
	}
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
		if (arg[i])
			printf(" ");
	}
	if (var == 0)
		printf("\n");
	return (0);
}