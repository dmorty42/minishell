/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:33:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/19 21:29:33 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_declare(t_node *data)
{
	int	i;
	int	fd_out;

	fd_out = 1;
	if (data->r.r_num || data->r.x_num)
		fd_out = data->r.r_fd;
	if (data->pipe_num < data->is_pipe - 1)
		fd_out = data->fd[data->pipe_num][1];
	i = 0;
	while (data->env_exp[i])
	{
		write(fd_out, "declare -x ", 11);
		ft_putstr_fd(data->env_exp[i], fd_out);
		write(fd_out, "\n", 1);
		free(data->env_exp[i++]);
	}
	free(data->env_exp);
}
