/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:12:56 by hubretec          #+#    #+#             */
/*   Updated: 2022/01/12 13:45:16 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_words(char const *s, char c)
{
	int	i;
	int	words;

	i = -1;
	words = 0;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			words++;
	return (words);
}

static int	wordlen(char const *s, char c, int start)
{
	int	tmp;

	tmp = start;
	while (s[start] != c && s[start])
		start++;
	return (start - tmp);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		tab[j] = (char *)malloc(sizeof(char) * (wordlen(s, c, i) + 1));
		if (!tab[j])
			return (0);
		k = 0;
		while (s[i] != c && s[i])
			tab[j][k++] = s[i++];
		tab[j++][k] = '\0';
	}
	tab[j] = 0;
	return (tab);
}
