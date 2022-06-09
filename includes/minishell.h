/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 04:29:14 by jrossett          #+#    #+#             */
/*   Updated: 2022/06/08 10:54:00 by hubretec         ###   ########.fr       */
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

typedef struct s_pipeline
{
	int		nb_pipes;
	int		nb_children;
	int		**pipes;
	pid_t	*children;
}	t_pipeline;

typedef struct s_data
{
	int			fd_in;
	int			fd_out;
	int			rtn_val;
	int			heredocs;
	char		*pwd;
	char		*line;
	char		*wrong_file;
	char		**path;
	t_list		*envp;
	t_list		*tokens;
	t_pipeline	pipeline;
}	t_data;

int		varlen(char *str);
int		is_redir(char *str);
int		get_quote(char *str);
int		is_builtin(char *str);
int		check_quotes(char *str);
int		ft_len_double(char **tab);
int		get_nb_pipes(t_list	*tokens);

void	exec(t_data *data);
void	expander(t_data *data);
void	rm_heredoc(t_data *data);
void	check_syntax(t_data *data);
void	free_tokens(t_list *tokens);
void	init_pipeline(t_data *data);
void	restore_redirs(t_data *data);
void	heredoc(t_data *data, char *eof);
void	tokenize(t_data *data, t_list *lst);
void	exec_cmd(char **args, t_data *data);
void	join_token(t_list *token, t_list *cut);
void	exec_builtin(char **args, t_data *data);
void	replace_token(t_data *data, t_list *cut);
void	make_redirs(t_data *data, t_list *start);

void	*free_tab(char	**tab);

char	*skip_spaces(char *str);
char	*ft_prompt(t_data *data);
char	*remove_quotes(char *str);
char	*cut_word(char *str, int *quote);
char	*search_env(char *str, t_data *data);
char	*replace_var(t_data *data, t_list *token, char *str);

t_list	*format(char *str);
t_list	*cut_token(char *str);
t_list	*skip_redirs(t_list	*tokens);
t_list	*skip_pipes(t_list *tokens, int pos);
t_list	*choose_token(t_list *node, char **path);
t_list	*search_token(t_list *tokens, int search);

char	**get_args(t_list *tokens);
char	**list_to_tab(t_list *lst);
char	**get_path_env(char *path);

// -----------------------------BUILTINS-----------------------------

int		vnb(char *s);
int		ft_cd(t_data *data, char **arg);
int		ft_pwd(t_data *data);
int		ft_echo(t_data *data, char **arg);
int		ft_unset(t_data *data, char **arg);
int		ft_export(t_data *data, char **arg);
int		ft_lstexport(t_data *data, char *str);
int		ft_exit(t_data *data, char *str, int exit_code, char **args);

void	ft_env(t_data *data);
void	ft_list_sort(t_list *list);
void	exit_cmd(int exit_code, t_data *data, char *str, char **args);
void	ft_numeric(int exit_code, t_data *data, char *str, char **args);

t_list	*create_list(char **envp);

void	print_tokens(t_list *tokens);
void	print_str_tokens(t_list *tokens);

#endif
