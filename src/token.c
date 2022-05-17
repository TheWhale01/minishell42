/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:28:57 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/17 00:22:49 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char *str)
{
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "&&", 2))
		return (1);
	else if (*str == '|' || *str == '>' || *str == '<'
		|| *str == '*' || *str == '&' || *str == '('
		|| *str == ')')
		return (1);
	return (0);
}

int	is_cmd(char *cmd, char **path)
{
	int			len;
	char		*str;
	struct stat	*path_stat;

	path_stat = malloc(sizeof(struct stat));
	if (!path_stat)
		return (0);
	stat(cmd, path_stat);
	if (!access(cmd, X_OK) && !S_ISDIR(path_stat->st_mode))
		return (1);
	while (*path)
	{
		str = ft_strjoin(*(path++), cmd);
		len = ft_strlen(str);
		if (str[len - 1] == ' ')
			str[len - 1] = '\0';
		if (!access(str, X_OK) && !S_ISDIR(path_stat->st_mode))
		{
			free(str);
			return (1);
		}
		free(str);
	}
	free(path_stat);
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
	else if (*str == '*')
		token->token = WILDCARD;
	else if (*str == '|')
		token->token = PIPE;
	else if (*str == '>')
		token->token = REDIR_OUT;
	else if (*str == '<')
		token->token = REDIR_IN;
	else if (*str == '(')
		token->token = OPEN_P;
	else if (*str == ')')
		token->token = CLOSE_P;
}

t_list	*choose_token(t_list *node, char **path)
{
	t_list	*new;
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = (char *)node->content;
	if (is_cmd(node->content, path))
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
