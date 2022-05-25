/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:28:57 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/25 19:11:17 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	return (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"));
}

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
	char		*str;
	struct stat	path_stat;

	stat(cmd, &path_stat);
	if (!access(cmd, X_OK) && !S_ISDIR(path_stat.st_mode))
		return (1);
	while (*path)
	{
		str = ft_strjoin(*(path++), cmd);
		stat(str, &path_stat);
		if (!access(str, X_OK) && !S_ISDIR(path_stat.st_mode))
		{
			free(str);
			return (1);
		}
		free(str);
	}
	return (0);
}

void	choose_op(t_token *token, char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		token->token = D_REDIR_OUT;
	else if (!ft_strncmp(str, "<<", 2))
		token->token = D_REDIR_IN;
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
	if (is_builtin(node->content) || is_cmd(node->content, path))
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
