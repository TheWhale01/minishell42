/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:26:48 by hubretec          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/09 15:25:19 by hubretec         ###   ########.fr       */
=======
/*   Updated: 2022/05/09 15:11:34 by jrossett         ###   ########.fr       */
>>>>>>> ccf5ebbf84091de439c02b2b1e4b41a782504676
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
	WILDCARD,
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
	t_list	*tokens;
}	t_data;

int		is_cmd(char *str, char **path);

void	print_lst(t_list *lst);
void	print_tokens(t_token *tokens);

void	*free_tab(char	**tab);

t_list	*format(char *str);

size_t	tablen(char **ptr);

char	**get_path_env(char **env);

// -----------------------------BUILTINS-----------------------------

int		ft_export(t_list *list, char c);

void	ft_env(t_list **list);
void	exit_cmd(int exit_code, t_data *data);

#endif
