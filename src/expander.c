/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:34:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/13 11:55:49 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_chars_before(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (*str == ' ')
		str++;
	if (*str == '\"')
		str++;
	while (str[i] && str[i] != '$')
		i++;
	if (!i)
		return (NULL);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, i);
	return (new);
}

char	*copy_chars_after(char *str)
{
	int		i;
	char	*new;

	while (*str && *str != '$')
		str++;
	str++;
	while (*str && (isalnum(*str) || *str == '_'))
		str++;
	if (!*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\"')
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, i);
	return (new);
}
