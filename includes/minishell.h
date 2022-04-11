/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:26:48 by hubretec          #+#    #+#             */
/*   Updated: 2022/04/08 15:36:25 by hubretec         ###   ########.fr       */
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
};

typedef struct s_token
{
	int		token;
	char	*str;
}	t_token;

void	print_tokens(t_token *tokens);

size_t	tablen(char **ptr);

t_token	*tokenize(char **str, char **env);

char	**get_path_env(char **env);

#endif
