/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:34:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/06 16:12:32 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote(char *str)
{
	while (*str && *str != '\'' && *str != '\"')
		str++;
	return (*str);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	quote;
	char	*new;

	quote = get_quote(str);
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	new = ft_strccpy(new, str, &quote);
	free(str);
	return (new);
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
		if (*str == '?' || ft_isdigit(*str))
			str++;
		else
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

char	*replace_var(t_data *data, t_list *token, char *str)
{
	char	*found;
	char	*start;

	found = search_env(str, data);
	found = ft_strjoin_free_s1_s2(copy_chars_before(
				((t_token *)token->content)->str, str), found);
	start = ft_strdup(found);
	found = ft_strjoin_free_s1_s2(found, copy_chars_after(str));
	free(((t_token *)token->content)->str);
	((t_token *)token->content)->str = found;
	str = ft_rstrstr(found, start);
	free(start);
	return (str);
}
