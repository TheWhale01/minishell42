/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/12 11:20:47 by hubretec         ###   ########.fr       */
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
	ft_lstclear(&lst, NULL);
}
