/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:56:12 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/07 14:46:42 by hubretec         ###   ########.fr       */
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

	restore_redirs(data, 0);
	filename = ((t_token *)file->content)->str;
	data->fd_in = dup(STDIN_FILENO);
	if (mode == D_REDIR_IN)
		heredoc(data, filename);
	else
	{
		file_fd = open(filename, O_RDONLY, 0644);
		if (file_fd == -1)
		{
			data->fd_in = -1;
			if (!data->wrong_file)
				data->wrong_file = filename;
			return ;
		}
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
	}
}

void	redir_out(t_data *data, t_list *file, int mode)
{
	int		file_fd;
	char	*filename;

	filename = ((t_token *)file->content)->str;
	data->fd_out = dup(STDOUT_FILENO);
	if (mode == D_REDIR_OUT)
		file_fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		data->fd_out = -1;
		if (!data->wrong_file)
			data->wrong_file = filename;
	}
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

void	restore_redirs(t_data *data, int msg)
{
	rm_heredoc(data);
	if (data->fd_in == -1)
	{
		if (msg)
			perror(data->wrong_file);
		data->fd_in = STDIN_FILENO;
	}
	else if (data->fd_in != STDIN_FILENO)
	{
		dup2(data->fd_in, STDIN_FILENO);
		close(data->fd_in);
	}
	if (data->fd_out == -1)
	{
		if (msg)
			perror(data->wrong_file);
		data->fd_in = STDOUT_FILENO;
	}
	else if (data->fd_out != STDOUT_FILENO)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	data->wrong_file = NULL;
}
