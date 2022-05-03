/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:26:48 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/03 19:46:06 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>

enum	e_token
{
	CMD,
	VAR,
	PIPE,
	WORDS,
	D_PIPE,
	REDIR_IN,
	REDIR_OUT,
	D_REDIR_IN,
	D_REDIR_OUT,
};

typedef struct s_token
{
	int		token;
	char	*str;
}	t_token;

typedef struct s_data
{
	char	*line;
	char	**path;
	t_token	*tokens;
}	t_data;

int		is_cmd(char *str, char **path);

void	tokenize(t_data *data);
void	print_tokens(t_token *tokens);
void	exit_cmd(int exit_code, t_data *data);

void	*free_tab(char	**tab);

t_list	*format(char *str);

size_t	tablen(char **ptr);

char	**get_path_env(char **env);

#endif
