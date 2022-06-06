/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teambersaw <teambersaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/03 17:46:39 by teambersaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*skip_redirs(t_list	*tokens)
{
	t_token	*token;
	t_list	*tmp;

	tmp = tokens;
	token = (t_token *)tmp->content;
	while (tmp && (token->token == REDIR_IN || token->token == REDIR_OUT
			|| token->token == D_REDIR_IN || token->token == D_REDIR_OUT))
	{
		tmp = tmp->next->next;
		token = (t_token *)tmp->content;
	}
	return (tmp);
}

void	redir_in(t_data *data, t_list *file, int mode)
{
	int		file_fd;
	char	*filename;

	if (!file)
		ft_exit(data, "Syntax Error: invalid redirection.", EXIT_FAILURE,
			NULL);
	restore_redirs(data);
	filename = ((t_token *)file->content)->str;
	data->fd_in = dup(STDIN_FILENO);
	if (mode == D_REDIR_IN)
		heredoc(data, filename);
	else
	{
		file_fd = open(filename, O_RDONLY, 0644);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
}

void	redir_out(t_data *data, t_list *file, int mode)
{
	int		file_fd;
	char	*filename;

	if (!file)
		ft_exit(data, "Syntax Error: invalid redirection.", EXIT_FAILURE,
			NULL);
	filename = ((t_token *)file->content)->str;
	data->fd_out = dup(STDOUT_FILENO);
	if (mode == D_REDIR_OUT)
		file_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

void	make_redirs(t_data *data, t_list *start)
{
	t_list	*tmp;
	t_token	*token;

	tmp = start;
	while (tmp && ((t_token *)tmp->content)->token != PIPE)
	{
		token = (t_token *)tmp->content;
		if (token->token == REDIR_OUT || token->token == D_REDIR_OUT)
			redir_out(data, tmp->next, token->token);
		else if (token->token == REDIR_IN || token->token == D_REDIR_IN)
			redir_in(data, tmp->next, token->token);
		tmp = tmp->next;
	}
}

void	restore_redirs(t_data *data)
{
	rm_heredoc(data);
	if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
}
