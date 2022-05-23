/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/23 12:43:53 by hubretec         ###   ########.fr       */
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
	while (*str)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
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

void	expander(t_data *data)
{
	char	*str;
	t_list	*tmp;

	tmp = data->tokens;
	while (tmp)
	{
		str = ((t_token *)tmp->content)->str;
		while (*str && ft_strchr(str, '$')
			&& get_quote(((t_token *)tmp->content)->str) != '\'')
		{
			while (*str && (*str != '$' || (*str == '$' && *(str + 1)
						&& *(str + 1) != '_' && *(str + 1) != '?'
						&& !ft_isalnum(*(str + 1)))))
				str++;
			if (*str)
				str = replace_var(data, tmp, str);
		}
		((t_token *)tmp->content)->str
			= remove_quotes(((t_token *)tmp->content)->str);
		tmp = tmp->next;
	}
}
