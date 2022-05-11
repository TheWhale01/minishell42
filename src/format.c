/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:41:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/11 17:11:50 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char c, char *charset, int *quote)
{
	while (*charset)
	{
		if (c == '\"' || c == '\'')
			*quote = 1;
		if ((*charset == ' ' || *charset == '$') && *quote)
			charset++;
		if (*(charset++) == c)
			return (1);
	}
	return (0);
}

int	wordlen(char *str, char *charset, int *quote)
{
	int	i;

	i = 0;
	while (str[i] && !is_in(str[i], charset, quote))
		i++;
	return (i);
}

int	get_sep(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "&&", 2))
		return (2);
	else if (*str == '|' || *str == '>' || *str == '<'
		|| *str == '*' || *str == '&' || *str == '('
		|| *str == ')')
		return (1);
	else
	{
		while (str[i] && str[i] != ' ' && str[i + 1] != '$')
			i++;
		if (str[i + 1] == '$')
			i++;
		return (i);
	}
	return (0);
}

char	*cut_word(char *str, int *quote)
{
	int			len;
	char		*word;

	if (*quote)
	{
		len = wordlen(str + 1, "\"\'", quote) + 1;
		if (str[len] == '\"' || str[len] == '\'')
		{
			len++;
			*quote = 0;
		}
	}
	else
		len = wordlen(str, " |<>&$*()", quote);
	if (!len)
		len = get_sep(str);
	while (str[len] == ' ')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word = ft_strncpy(word, str, len);
	return (word);
}

t_list	*format(char *str)
{
	int		quote;
	char	*word;
	t_list	*lst;
	t_list	*node;

	quote = 0;
	lst = NULL;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			quote = 1;
		word = cut_word(str, &quote);
		node = ft_lstnew(word);
		if (!node)
		{
			free(word);
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, node);
		str += ft_strlen(word);
	}
	return (lst);
}
