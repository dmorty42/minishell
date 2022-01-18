/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:24 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/18 17:07:19 by dmorty           ###   ########.fr       */
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
		fd_out = data->r.r_fd;
	if (data->is_pipe)
		fd_out = data->fd[data->pipe_num][1];
	while (temp)
	{
		if (!temp->flag)
		{	
			if (temp->key && temp->value)
			{
				ft_putstr_fd(temp->key, fd_out);
				write(fd_out, "=", 1);
				ft_putstr_fd(temp->value, fd_out);
				write(fd_out, "\n", 1);
			}
		}
		temp = temp->next;
	}
	data->exit_status = 0;
}

void	change_out(t_node *data, int *fd)
{
	if (data->r.r_num || data->r.x_num)
		*fd = data->r.r_fd;
	if (data->is_pipe)
		*fd = data->fd[data->pipe_num][1];
}

void	find_direct(t_node *data, char **path)
{
	if (!data->cmd[1])
		*path = ft_strjoin(data->home, "/");
	else if (!ft_strcmp(data->cmd[1], "-"))
	{
		*path = find_old_pwd(data);
		if (*path)
		{
			write(2, *path, ft_strlen(*path));
			write(2, "\n", 1);
		}
	}
	else if (data->cmd[1])
		*path = ft_strdup(data->cmd[1]);
}
