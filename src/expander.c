/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 20:34:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/17 04:47:15 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		len;
	int		quote;
	char	*new;

	i = 0;
	quote = 0;
	len = ft_strlen(str) - 2;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (*str)
	{
		if (!quote && (*str == '\"' || *str == '\''))
			quote = *(str++);
		if ((quote == '\'' && *str == '\'') || (quote == '\"' && *str == '\"'))
		{
			str++;
			quote = 0;
		}
		new[i++] = *str++;
	}
	new[i] = '\0';
	return (new);
}

int	get_quote(char *str)
{
	while (*str && *str != '\'' && *str != '\"')
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

	found = search_env(str, data->envp);
	found = ft_strjoin_free_s1(copy_chars_before(
				((t_token *)token->content)->str, str), found);
	start = ft_strdup(found);
	found = ft_strjoin_free_s1(found, copy_chars_after(str));
	free(((t_token *)token->content)->str);
	((t_token *)token->content)->str = found;
	str = ft_rstrstr(found, start);
	return (str);
}
