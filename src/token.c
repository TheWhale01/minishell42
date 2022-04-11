/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:18:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/09 18:35:18 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *str)
{
	struct stat	path_stat;

	stat(str, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	is_cmd(char *str, char **path)
{
	char		*full_path;

	if (check_dir(str) && !access(str, F_OK | X_OK))
		return (1);
	while (*path)
	{
		full_path = ft_strjoin(*path, str);
		if (!access(full_path, F_OK | X_OK))
			return (1);
		path++;
	}
	return (0);
}

void	choose_token(char *str, char **path, t_token *tokens)
{
	tokens->str = ft_strdup(str);
	free(str);
	if (is_cmd(tokens->str, path))
		tokens->token = CMD;
	else if (tokens->str[0] == '$' && ft_strlen(tokens->str) > 1)
		tokens->token = VAR;
	else if (!ft_strcmp(tokens->str, "|"))
		tokens->token = PIPE;
	else if (!ft_strcmp(tokens->str, "||"))
		tokens->token = D_PIPE;
	else
		tokens->token = WORDS;
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
	free(str);
	tokens[i].str = NULL;
	return (tokens);
}
