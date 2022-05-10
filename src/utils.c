/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/10 10:21:16 by hubretec         ###   ########.fr       */
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
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	print_tokens(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (((t_token *)tmp->content)->token == CMD)
			printf("CMD ");
		else if (((t_token *)tmp->content)->token == PIPE)
			printf("PIPE ");
		else if (((t_token *)tmp->content)->token == D_PIPE)
			printf("D_PIPE ");
		else if (((t_token *)tmp->content)->token == D_REDIR_IN)
			printf("D_REDIR_IN ");
		else if (((t_token *)tmp->content)->token == D_REDIR_OUT)
			printf("D_REDIR_OUT ");
		else if (((t_token *)tmp->content)->token == REDIR_IN)
			printf("REDIR_IN ");
		else if (((t_token *)tmp->content)->token == REDIR_OUT)
			printf("REDIR_OUT ");
		else if (((t_token *)tmp->content)->token == AND)
			printf("AND ");
		else if (((t_token *)tmp->content)->token == WILDCARD)
			printf("WILDCARD ");
		else if (((t_token *)tmp->content)->token == VAR)
			printf("VAR ");
		else if (((t_token *)tmp->content)->token == OPEN_P)
			printf("OPEN_P ");
		else if (((t_token *)tmp->content)->token == CLOSE_P)
			printf("CLOSE_P ");
		else
			printf("WORD ");
		tmp = tmp->next;
	}
	printf("\n");
}
