/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:41:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/20 10:02:50 by hubretec         ###   ########.fr       */
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

int	wordlen(char *str, char *charset, int *quote)
{
	int		i;

	i = 0;
	while (str[i] && !ft_is_in(str[i], charset))
	{
		if (!*quote && (str[i] == '\"' || str[i] == '\''))
		{
			if (str[i++] == '\'')
				*quote = 1;
			else
				*quote = 2;
		}
		while (str[i] && ((*quote == 2 && str[i] != '\"')
				|| (*quote == 1 && str[i] != '\'')))
			i++;
		if ((*quote == 2 && str[i] == '\"') || (*quote == 1 && str[i] == '\''))
		{
			*quote = 0;
			return (i + 1);
		}
		i++;
	}
	return (i);
}

int	get_sep(char *str)
{
	int	i;

	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "&&", 2)
		|| !ft_strncmp(str, "$?", 2))
		return (2);
	else if (*str == '|' || *str == '>' || *str == '<'
		|| *str == '*' || *str == '&' || *str == '('
		|| *str == ')')
		return (1);
	else
	{
		i = 0;
		if (ft_isdigit(str[i + 1]))
			return (2);
		while (str[i] && str[i] != ' '
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i++;
		return (i + 1);
	}
	return (0);
}

char	*cut_word(char *str, int *quote)
{
	int			len;
	char		*word;

	if (!*str)
		return (NULL);
	len = wordlen(str, " |<>()*$&", quote);
	if (!len)
		len += get_sep(&str[len]);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word = ft_strncpy(word, str, len);
	return (word);
}
