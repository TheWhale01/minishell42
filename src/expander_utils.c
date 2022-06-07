/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:00:29 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/07 09:41:17 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenlen(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		quote = str[i];
		i++;
	}
	while (str[i] && ((!quote && str[i] != '\'' && str[i] != '\"')
			|| (quote && str[i] != quote)))
		i++;
	if (quote && str[i] == quote)
		i++;
	return (i);
}

void	join_token(t_list *token, t_list *cut)
{
	t_list	*tmp;
	char	*str;

	tmp = cut;
	str = NULL;
	while (tmp)
	{
		str = ft_strjoin_free_s1_s2(str, tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&cut, NULL);
	free(((t_token *)token->content)->str);
	((t_token *)token->content)->str = str;
}

void	replace_token(t_data *data, t_list *cut)
{
	int		quote;
	char	*str;
	t_list	*tmp;

	tmp = cut;
	while (tmp)
	{
		quote = get_quote(tmp->content);
		tmp->content = remove_quotes(tmp->content);
		str = tmp->content;
		while (*str && ft_strchr(str, '$') && quote != '\'')
		{
			while (*str && (*str != '$' || (*str == '$' && *(str + 1)
						&& *(str + 1) != '_' && *(str + 1) != '?'
						&& !ft_isalnum(*(str + 1)))))
				str++;
			if (*str)
				str = replace_var(data, tmp, str);
		}
		tmp = tmp->next;
	}
}

t_list	*cut_token(char *str)
{
	int		len;
	char	*new_str;
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (*str)
	{
		len = tokenlen(str);
		new_str = malloc(sizeof(char) * (len + 1));
		ft_strncpy(new_str, str, len);
		if (!new_str)
			return (NULL);
		node = ft_lstnew(new_str);
		ft_lstadd_back(&new, node);
		str += len;
	}
	return (new);
}
