/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:28:57 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/10 09:43:11 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char *str)
{
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "&&", 2))
		return (1);
	else if (*str == '|' || *str == '>' || *str == '<'
		|| *str == '*' || *str == '&')
		return (1);
	return (0);
}

int	is_cmd(char *cmd, char **path)
{
	int		len;
	char	*str;

	while (*path)
	{
		str = ft_strjoin(*path, cmd);
		len = ft_strlen(str);
		if (str[len - 1] == ' ')
			str[len - 1] = '\0';
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

void	choose_op(t_token *token, char *str)
{
	if (!ft_strncmp(str, "||", 2))
		token->token = D_PIPE;
	else if (!ft_strncmp(str, ">>", 2))
		token->token = D_REDIR_OUT;
	else if (!ft_strncmp(str, "<<", 2))
		token->token = D_REDIR_IN;
	else if (!ft_strncmp(str, "&&", 2))
		token->token = AND;
	else if (!ft_strncmp(str, "\"*", 2) || *str == '*')
		token->token = WILDCARD;
	else if (*str == '|')
		token->token = PIPE;
	else if (*str == '>')
		token->token = REDIR_OUT;
	else if (*str == '<')
		token->token = REDIR_IN;
}

t_list	*choose_token(t_list *node, char **path)
{
	t_list	*new;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = (char *)node->content;
	if (is_cmd(token->str, path))
		token->token = CMD;
	else if (is_op(node->content))
		choose_op(token, node->content);
	else if (*(char *)(node->content) == '$'
		|| !ft_strncmp(node->content, "\"$", 2))
		token->token = VAR;
	else
		token->token = WORD;
	new = ft_lstnew(token);
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
