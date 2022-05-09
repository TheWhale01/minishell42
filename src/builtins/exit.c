/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:33:59 by hubretec          #+#    #+#             */
/*   Updated: 2022/05/09 19:42:10 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(int exit_code, t_data *data)
{
	free(data->line);
	free_tab(data->path);
	ft_lstclear(&data->tokens, free);
	exit(exit_code);
}
