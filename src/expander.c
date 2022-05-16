/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:34:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/17 01:24:32 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	str++;
	if (ft_isdigit(*str) || *str == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int	get_quote(char *str)
{
	while (str && *str && *str != '\'' && *str != '\"')
		str++;
	return (*str);
}

char	*copy_chars_before(char *str, char *end)
{
	int		i;
	char	*stop;
	char	*new;

	i = 0;
	stop = ft_strstr(str, end);
	while (&str[i] != stop)
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
	int		len;
	char	*new;

	if (*str == '$')
	{
		str++;
		while (*str && (*str == '_' || *str == '?' || ft_isalnum(*str)))
			str++;
	}
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, len);
	return (new);
}
