/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:38:19 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/28 03:45:54 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_binary(t_node *data, char **env)
{
	char	*temp;
	int		i;

	i = -1;
	temp = NULL;
	while (data->path[++i])
	{
		temp = NULL;
		temp = ft_strjoin(data->path[i], "/");
		temp = ft_strjoin(temp, data->cmd[0]);
		if (access(temp, X_OK) == 0)
			execve(temp, data->cmd, env);
	}
	printf("minishell: %s: command not found\n", data->cmd[0]);
	exit(EXIT_FAILURE);
}

void	change_fd(t_node *data)
{
	if (data->pipe_num < data->is_pipe)
	{
		pipe_dup(data);
	}
	if (data->her.is_heredoc)
		dup2(data->her.fd[0], 0);
	if (data->r.l_num || data->r.r_num)
	{
		if (data->r.l_num)
			dup2(data->r.l_fd, 0);
		if (data->r.r_num)
			dup2(data->r.r_fd, 1);
	}
}

void	execute_cmd(t_node *data, char **env)
{
	int		pid;

	if (data->pipe_num > 0 && data->pipe_num < data->is_pipe)
	{
		close(data->fd[data->pipe_num - 1][1]);
	}
	pid = fork();
	if (pid == 0)
	{
		change_fd(data);
		if (!data->is_err && buildin_1(data))
			find_binary(data, env);
		else
			exit(EXIT_FAILURE);
	}
	if (pid > 0)
		wait(NULL);
	if (pid > 0 && data->pipe_num < data->is_pipe - 1)
		execute_pipe(data, env);
}
