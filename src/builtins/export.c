/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:12:46 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/16 16:26:34 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_verif(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	i++;
	while (str[i] && str[i] != ' ')
		i++;
	return (0);
}

int	ft_export(t_data *data)
{
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	token = (t_token *)tmp->content;
	if (ft_lstsize(tmp) == 1)
		return (ft_list_sort(&data->env), 0);
	tmp = tmp->next;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("PRINTF: %s\n", token->str);
		if (ft_verif(token->str))
			printf("ERROR\n");
		else if (ft_double)
		{
			ft_lstadd_back(&data->env, ft_lstnew(token->str));
			ft_env(&data->env);
			printf("VALIDE\n");
		}
		tmp = tmp->next;
	}
	return (0);
}
