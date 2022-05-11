/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/11 16:27:48 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			free_tokens(data->tokens);
			return ;
		}
		ft_lstadd_back(&data->tokens, node);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, NULL);
}

void	expander(t_data *data)
{
	t_list	*tmp;
	t_list	*found;
	t_token	*token;

	tmp = data->tokens;
	while (tmp)
	{
		token = ((t_token *)tmp->content);
		if (token->token == VAR)
		{
			found = ft_lstsearch(data->envp, token->str,
					sizeof(char *) * ft_strlen(token->str));
			if (found)
			{
				free(token->str);
				token->str = ft_strdup((char *)found->content);
			}
		}
		tmp = tmp->next;
	}
}
