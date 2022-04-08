/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:18:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/08 09:24:14 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *str, char **path)
{
	if (!access(str, F_OK))
		return (1);	
	while (*path)
		if (!access(ft_strjoin(*(path++), str), F_OK))
			return (1);
	return (0);
}

void	choose_token(char *str, char **path, t_token *tokens)
{
	tokens->str = ft_strdup(str);
	free(str);
	if (is_cmd(tokens->str, path))
		tokens->token = CMD;
	else if (tokens->str[0] == '$')
		tokens->token = VAR;
	else if (tokens->str[0] == '|')
		tokens->token = PIPE;
	else if (!ft_strcmp(tokens->str, "||"))
		tokens->token = D_PIPE;
}

t_token	*tokenize(char **str, char **path)
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
		tokens[i].token = -1;
		choose_token(str[i], path, &tokens[i]);
		if (tokens[i].token == -1)
		{
			free(tokens);
			return (NULL);
		}
	}
	printf("Je ne suis pas moi\n");
	free(str);
	return (tokens);
}
