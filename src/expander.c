/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:34:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/17 04:23:13 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	quote;

	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\"' || *str == '\''))
		{
			if (*(str++) == '\'')
				quote = 1;
			else
				quote = 2;
		}
		while (*str && ((quote == 2 && *str != '\"')
				|| (quote == 1 && *str != '\'')))
			str++;
		if ((quote == 1 && *str == '\'') || (quote == 2 && *str == '\"'))
			quote = 0;
		str++;
	}
	return (!quote);
}

int	get_quote(char *str)
{
	while (str && *str && *str != '\'' && *str != '\"')
		str++;
	return (*str);
}

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
	if (*str == '?')
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
