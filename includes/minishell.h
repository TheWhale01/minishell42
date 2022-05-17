/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:26:48 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/16 19:04:43 by jrossett         ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>

enum	e_token
{
	CMD,
	VAR,
	AND,
	PIPE,
	WORD,
	D_PIPE,
	OPEN_P,
	CLOSE_P,
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
	t_list	*envp;
	t_list	*tokens;
}	t_data;

int		varlen(char *str);
int		get_quote(char *str);
int		check_quotes(char *str);
int		only_spaces(char *str, int len);

void	expander(t_data *data);
void	free_tokens(t_list *tokens);
void	tokenize(t_data *data, t_list *lst);

void	*free_tab(char	**tab);
void	free_list(t_list *list);

char	*skip_spaces(char *str);
char	*copy_chars_after(char *str);
char	*copy_chars_before(char *str);
char	*cut_word(char *str, int *quote);
char	*search_env(char *str, t_list *envp);

t_list	*format(char *str);
t_list	*choose_token(t_list *node, char **path);

size_t	tablen(char **ptr);

char	**get_path_env(char **env);

// -----------------------------BUILTINS-----------------------------

int		ft_export(t_data *data);

void	ft_env(t_list **list);
void	free_list(t_list *list);
void	ft_list_sort(t_list *list);
void	exit_cmd(int exit_code, t_data *data, char *str);

t_list	*create_list(char **envp);

// -----------------------------TMP-----------------------------

void	print_lst(t_list *lst);
void	print_tokens(t_list *tokens, int mode);

#endif
