/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:29:14 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/25 20:51:00 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

enum	e_token
{
	CMD,
	VAR,
	PIPE,
	WORD,
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
	int		fd_in;
	int		fd_out;
	int		rtn_val;
	char	*line;
	char	**path;
	char	*pwd;
	t_list	*envp;
	t_list	*tokens;
}	t_data;

int		get_quote(char *str);
int		is_builtin(char *str);
int		check_quotes(char *str);
int		only_spaces(char *str, int len);

void	exec(t_data *data);
void	expander(t_data *data);
void	free_list(t_list *list);
void	make_redirs(t_data *data);
void	free_tokens(t_list *tokens);
void	restore_redirs(t_data *data);
void	tokenize(t_data *data, t_list *lst);

void	*free_tab(char	**tab);

char	*skip_spaces(char *str);
char	*remove_quotes(char *str);
char	*cut_word(char *str, int *quote);
char	*search_env(char *str, t_data *data);
char	*replace_var(t_data *data, t_list *token, char *str);

t_list	*format(char *str);
t_list	*skip_redirs(t_list	*tokens);
t_list	*choose_token(t_list *node, char **path);
t_list	*search_token(t_list *tokens, int search);

size_t	tablen(char **ptr);

char	**get_path_env(char **env);
char	**list_to_tab(t_list *lst);

// -----------------------------BUILTINS-----------------------------

int		ft_cd(t_data *data);
int		ft_pwd(t_data *data);
int		ft_echo(t_list *tokens, t_data *data);
int		ft_unset(t_data *data);
int		ft_export(t_data *data);
int		ft_lstexport(t_list **lst, char *str);

void	ft_env(t_data *data);
void	ft_list_sort(t_list *list);
void	exit_cmd(int exit_code, t_data *data, char *str);

t_list	*create_list(char **envp);

void	print_tab(char **tab);

#endif
