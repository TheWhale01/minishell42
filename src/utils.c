/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/09 16:51:57 by hubretec         ###   ########.fr       */
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

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		printf("%s$\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*tmp_token;

	tmp = tokens;
	while (tmp)
	{
		tmp_token = (t_token *)tmp->content;
		if (tmp_token->token == CMD)
			printf("CMD ");
		else if (tmp_token->token == VAR)
			printf("VAR ");
		else if (tmp_token->token == PIPE)
			printf("PIPE ");
		else if (tmp_token->token == D_PIPE)
			printf("D_PIPE ");
		else if (tmp_token->token == REDIR_OUT)
			printf("REDIR_OUT ");
		else if (tmp_token->token == WORD)
			printf("WORD ");
		tmp = tmp->next;
	}
	printf("\n");
}
