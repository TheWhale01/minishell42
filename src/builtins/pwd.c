/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrossett <jrossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 07:40:34 by jrossett          #+#    #+#             */
/*   Updated: 2022/05/31 14:57:24 by jrossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;

	(void) data;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("%s\n", data->pwd);
		return (1);
	}
	free(data->pwd);
	data->pwd = pwd;
	printf("%s\n", data->pwd);
	return (0);
}
