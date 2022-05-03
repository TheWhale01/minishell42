/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/03 19:16:34 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**get_path_env(char **env)
{
	int		i;
	char	**path;

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
		{
			i = -1;
			path = ft_split(&((*env)[5]), ':');
			while (path[++i])
				path[i] = ft_strjoin_free_s1(path[i], "/");
			return (path);
		}
		env++;
	}
	return (NULL);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = -1;
	while (tokens[++i].str)
	{
		if (tokens[i].token == CMD)
			printf("CMD ");
		else if (tokens[i].token == VAR)
			printf("VAR ");
		else if (tokens[i].token == PIPE)
			printf("PIPE ");
		else if (tokens[i].token == D_PIPE)
			printf("D_PIPE ");
		else if (tokens[i].token == REDIR_OUT)
			printf("REDIR_OUT ");
		else if (tokens[i].token == WORDS)
			printf("WORDS ");
	}
	printf("\n");
}
