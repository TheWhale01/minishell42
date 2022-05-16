/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:07 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/16 15:59:08 by hubretec         ###   ########.fr       */
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
		while (*str == ' ')
			str++;
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
	char	*found;
	t_list	*tmp;
	t_token	*token;

	tmp = data->tokens;
	while (tmp)
	{
		token = ((t_token *)tmp->content);
		if (!check_quotes(token->str))
			exit_cmd(EXIT_FAILURE, data, "Syntax Error: Non matching quotes.");
		while (ft_strchr(token->str, '$') && get_quote(token->str) != '\'')
		{
			found = search_env(token->str, data->envp);
			found = ft_strjoin_free_s1(
					copy_chars_before(token->str), found);
			found = ft_strjoin_free_s1(found, copy_chars_after(token->str));
			free(token->str);
			token->str = found;
		}
		tmp = tmp->next;
	}
}
