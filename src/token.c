/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:28:57 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/09 16:54:03 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd(char *cmd, char **path)
{
	char	*str;

	while (*path)
	{
		str = ft_strjoin(*path, cmd);
		printf("%s\n", str);
		if (!access(str, F_OK | X_OK))
		{
			free(str);
			return (1);
		}
		free(str);
		path++;
	}
	return (0);
}

t_list	*choose_token(t_list *node, char **path)
{
	t_list	*new;
	t_token	token;

	token.str = (char *)node->content;
	if (is_cmd(token.str, path))
		token.token = CMD;
	else
		token.token = WORD;
	new = ft_lstnew(&token);
	return (new);
}

void	tokenize(t_data *data, t_list *lst)
{
	t_list	*tmp;
	t_list	*node;

	tmp = lst;
	data->tokens = NULL;
	while (tmp)
	{
		node = choose_token(tmp, data->path);
		if (!node)
			return ;
		ft_lstadd_back(&data->tokens, node);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, NULL);
}
