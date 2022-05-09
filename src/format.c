/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:41:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/09 13:10:06 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char c, char *charset)
{
	while (*charset)
		if (*(charset++) == c)
			return (1);
	return (0);
}

int	wordlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !is_in(str[i], charset))
		i++;
	return (i);
}

int	get_ops(char *str)
{
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "&&", 2))
		return (2);
	else if (*str == '|' || *str == '>' || *str == '<'
		|| *str == '*' || *str == '&')
		return (1);
	return (0);
}

char	*cut_word(char *str, int *quote)
{
	int			len;
	char		*word;

	if (*str != '$' && *str != '*' && *quote)
	{
		len = wordlen(str + 1, "$\"*") + 1;
		if (str[len] == '\"')
		{
			len++;
			*quote = 0;
		}
	}
	else
		len = wordlen(str, " |<>&*");
	if (!len)
		len = get_ops(str);
	while (str[len] == ' ')
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word = ft_strncpy(word, str, len);
	word[len] = '\0';
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
		if (*str == '\"')
			quote = 1;
		word = cut_word(str, &quote);
		node = create_node(word);
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
