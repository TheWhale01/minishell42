/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/30 15:51:47 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_data *data)
{
	char	*dir;
	char	*line;
	char	*prompt;

	dir = ft_rstrstr(data->pwd, search_env("HOME", data));
	if (!dir)
		dir = data->pwd;
	else
		dir = ft_strjoin("~", dir);
	prompt = ft_strjoin(search_env("USER", data), "@minishell:");
	if (!ft_strchr(dir, '~'))
		prompt = ft_strjoin_free_s1(prompt, dir);
	else
		prompt = ft_strjoin_free_s1_s2(prompt, dir);
	prompt = ft_strjoin_free_s1(prompt, "$ ");
	line = readline(prompt);
	free(prompt);
	return (line);
}

void	init(t_data *data)
{
	data->fd_in = STDIN;
	data->fd_out = STDOUT;
	data->rtn_val = 0;
	data->heredocs = 0;
	data->line = NULL;
	data->path = NULL;
	data->envp = NULL;
	data->tokens = NULL;
	data->pwd = getcwd(NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	t_list	*lst;

	(void)ac;
	(void)av;
	init(&data);
	data.envp = create_list(envp);
	data.path = get_path_env(envp);
	while (1)
	{
		data.line = ft_prompt(&data);
		add_history(data.line);
		if (!check_quotes(data.line))
			exit_cmd(EXIT_FAILURE, &data,
				"Syntax Error: mismatched opening and closing quotes.");
		lst = format(data.line);
		tokenize(&data, lst);
		expander(&data);
		exec(&data);
		free_tokens(data.tokens);
	}
	return (0);
}
