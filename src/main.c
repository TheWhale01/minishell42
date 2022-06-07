/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:33:00 by hubretec          #+#    #+#             */
/*   Updated: 2022/06/07 13:46:03 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_data *data)
{
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	data->rtn_val = 0;
	data->heredocs = 0;
	data->line = NULL;
	data->path = NULL;
	data->envp = NULL;
	data->wrong_file = NULL;
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
			ft_exit(&data,
				"Syntax Error: mismatched opening and closing quotes.",
				EXIT_FAILURE, NULL);
		lst = format(data.line);
		tokenize(&data, lst);
		check_syntax(&data);
		expander(&data);
		if (data.tokens)
			exec(&data);
		free_tokens(data.tokens);
	}
	return (0);
}
