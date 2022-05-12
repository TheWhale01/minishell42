/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/12 15:12:36 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*format(char *str)
{
	int		quote;
	char	*word;
	t_list	*lst;
	t_list	*node;

	quote = 0;
	lst = NULL;
	while (*str && !only_spaces(str, ft_strlen(str)))
	{
		word = cut_word(str, &quote);
		if (!word)
			return (ft_lstclear(&lst, free));
		node = ft_lstnew(word);
		if (!node)
		{
			free(word);
			return (ft_lstclear(&lst, free));
		}
		ft_lstadd_back(&lst, node);
		str += ft_strlen(word);
	}
	return (lst);
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
		{
			free_tokens(data->tokens);
			return ;
		}
		ft_lstadd_back(&data->tokens, node);
		tmp = tmp->next;
	}
	lst = ft_lstclear(&lst, NULL);
}

void	expander(t_data *data)
{
	t_list	*found;
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	while (tmp)
	{
		token = ((t_token *)tmp->content);
		if (token->token == VAR
			|| (token->token == WORD && ft_strchr(token->str, '$')))
		{
			found = search_env(skip_spaces(token->str) + 1, data->envp);
			if (found)
			{
				token->str = ft_strdup(ft_strchr((char *)found->content, '=') + 1);
			}
		}
		tmp = tmp->next;
	}
}
