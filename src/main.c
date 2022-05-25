/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/25 16:28:26 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data)
{
	data->fd_in = STDIN;
	data->fd_out = STDOUT;
	data->rtn_val = 0;
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
		data.line = readline("minishell> ");
		if (!check_quotes(data.line))
			exit_cmd(EXIT_FAILURE, &data,
				"Syntax Error: mismatched opening and closing quotes.");
		lst = format(data.line);
		tokenize(&data, lst);
		expander(&data);
		exec_cmd(&data);
		free_tokens(data.tokens);
	}
	return (0);
}
