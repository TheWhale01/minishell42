/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:00:29 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/06 19:43:59 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenlen(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i];
		i++;
	}
	while (str[i] && ((!quote && str[i] != '\'' && str[i] != '\"')
			|| (quote && str[i] != quote)))
		i++;
	if (quote && str[i] == quote)
		i++;
	return (i);
}

t_list	*cut_token(char *str)
{
	int		len;
	char	*new_str;
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (*str)
	{
		len = tokenlen(str);
		new_str = malloc(sizeof(char) * (len + 1));
		ft_strncpy(new_str, str, len);
		if (!new_str)
			return (NULL);
		node = ft_lstnew(new_str);
		ft_lstadd_back(&new, node);
		str += len;
	}
	return (new);
}
