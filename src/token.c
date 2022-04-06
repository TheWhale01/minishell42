/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:18:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/06 22:37:33 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *str, char **env)
{
	if (!access(str, F_OK))
		return (1);
	else
		while (*env)
			if (!access(ft_strjoin(*(env++), str), F_OK))
				return (1);
	return (0);
}

t_token	*tokenize(char **str, char **env)
{
	int		i;
	int		nb_words;
	t_token	*tokens;

	nb_words = tablen(str);
	tokens = malloc(sizeof(t_token) * (nb_words + 1));
	if (!tokens)
		return (NULL);
	i = -1;
	while (++i < nb_words)
	{
		tokens->str = str[i];
		if (is_cmd(str[i], env))
			tokens->token = CMD;
		else if (str[i][0] == '$')
			tokens->token = VAR;
		else if (str[i][0] == '|')
			tokens->token = PIPE;
		else
		{
			free(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
