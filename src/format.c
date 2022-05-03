/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:41:51 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/03 20:26:30 by hubretec         ###   ########.fr       */
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

char	*cut_word(char *str)
{
	int		len;
	char	*word;

	len = 0;
	if (*str == '\"')
	{
		str++;
		while (str[len] && str[len] != '\"' && str[len] != '$')
			len++;
		printf("%d\n", str[len]);
	}
	else if (*str != '\0')
	{
		len = wordlen(str);
		while (str[len] == ' ')
			len++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word = ft_strncpy(word, str, len);
	word[len] = '\0';
	return (word);
}

t_list	*format(char *str)
{
	char	*word;
	t_list	*lst;

	lst = NULL;
	while (*str)
	{
		word = cut_word(str);
		//printf("%s\t%ld\n", word, ft_strlen(word));
		str += ft_strlen(word);
	}
	return (lst);
}
