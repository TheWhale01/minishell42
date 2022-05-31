/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:24:31 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:10 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

t_list	*search_token(t_list *tokens, int search)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->token == search)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_path_env(char **env)
{
	int		i;
	char	**path;

	while (env && *env)
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

char	**list_to_tab(t_list *lst)
{
	int		i;
	char	**tab;
	t_list	*tmp;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		tab[i++] = (char *)tmp->content;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_tokens(t_list *tokens)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		printf("%s ", token->str);
		tmp = tmp->next;
	}
	printf("\n");
}
