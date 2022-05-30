/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:55:11 by teambersaw        #+#    #+#             */
/*   Updated: 2022/05/25 21:33:37 by teambersaw       ###   ########.fr       */
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

int	ft_echo(t_data *data)
{
	t_list	*tmp;
	t_token	*token;
	int		var;

	var = 0;
	tmp = data->tokens;
	token = (t_token *)tmp->content;
	if (ft_lstsize(tmp) == 1)
		return (printf("\n"), 0);
	tmp = tmp->next;
	token = (t_token *)tmp->content;
	while (tmp && ft_option(token->str))
	{
		var = 1;
		tmp = tmp->next;
		if (tmp)
			token = (t_token *)tmp->content;
	}
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("%s", token->str);
		tmp = tmp->next;
		if (tmp)
			printf(" ");
	}
	if (var == 0)
		printf("\n");
	return (0);
}