/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:41:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/04 14:00:35 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"')
		i++;
	return (i);
}

char	*cut_word(char *str, int *quote)
{
	int		len;
	char	*word;

	len = 0;
	if (*quote && str[len] != '$')
	{
		while (str[len] && str[len] != '\"' && str[len] != '$')
			len++;
		if (str[len]== '\"')
			*quote = 0;
	}
	else
		len = wordlen(str);
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
		{
			quote = 1;
			str++;
		}
		word = cut_word(str, &quote);
		node = create_node(word);
		if (!node)
			return (NULL);
		ft_lstadd_back(&lst, node);
		str += ft_strlen(word);
		while (*str == ' ')
			str++;
	}
	return (lst);
}
