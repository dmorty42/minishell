/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:24 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/14 02:51:33 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_f(t_node *data)
{
	t_env	*temp;
	int		fd_out;

	fd_out = 1;
	temp = data->env_lst;
	if (data->r.r_num || data->r.x_num)
	{
		fd_out = data->r.r_fd;
	}
	if (data->is_pipe)
	{
		fd_out = data->fd[data->pipe_num][1];
	}
	while (temp)
	{
		ft_putstr_fd(temp->key, fd_out);
		write(fd_out, "=", 1);
		ft_putstr_fd(temp->value, fd_out);
		write(fd_out, "\n", 1);
		temp = temp->next;
	}
}
