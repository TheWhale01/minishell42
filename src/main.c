/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/31 16:57:30 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data.path = get_path_env(search_env("PATH", &data));
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
