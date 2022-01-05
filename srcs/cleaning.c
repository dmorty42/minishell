/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:47:49 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/05 15:01:12 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	more_clean(t_node *data)
{
	int	i;

	i = -1;
	if (data->temp)
	{
		while (data->temp[++i])
			free(data->temp[i]);
		free(data->temp);
		data->temp = NULL;
	}
	i = -1;
	if (data->fd)
	{
		while (++i < data->is_pipe - 1)
		{
			close(data->fd[i][0]);
			close(data->fd[i][1]);
			free(data->fd[i]);
		}
		free(data->fd);
		data->fd = NULL;
	}
	data->pipe_num = 10;
	data->is_pipe = 0;
}

void	cmd_clean(t_node *data)
{
	int	i;

	i = -1;
	if (data->cmd)
	{
		while (data->cmd[++i])
			free(data->cmd[i]);
		free(data->cmd);
		data->cmd = NULL;
	}
}

void	cycle_clean(t_node *data, int flag)
{
	cmd_clean(data);
	data->is_err = 0;
	if (data->r.l_num)
	{
		close(data->r.l_fd);
		data->r.l_num = 0;
	}
	if (data->r.r_num)
	{
		close(data->r.r_fd);
		data->r.r_num = 0;
	}
	if (data->her.is_heredoc)
	{
		data->her.is_heredoc = 0;
		close(data->her.fd[0]);
	}
	if (flag == 1)
		more_clean(data);
}
