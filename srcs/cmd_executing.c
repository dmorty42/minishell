/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 02:38:19 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/11 02:11:31 by dmorty           ###   ########.fr       */
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

void	parse_path(t_node *data)
{
	t_env	*temp;

	temp = data->env_lst;
	while (temp)
	{
		if (!ft_strncmp("PATH", temp->key, 4))
			data->path = ft_split(temp->value, ':');
		temp = temp->next;
	}
}

void	execute_cmd(t_node *data, char **env)
{
	int		pid;
	int		i;

	pid = 0;
	if (data->pipe_num > 0 && data->pipe_num < data->is_pipe)
	{
		close(data->fd[data->pipe_num - 1][1]);
	}
	if (buildin_1(data))
	{
		pid = fork();
		if (pid == 0)
		{
			change_fd(data);
			if (!data->is_err)
				find_binary(data, env);
			else
				exit(EXIT_FAILURE);
		}
	}
	if (pid > 0)
	{
		waitpid(pid, &i, 0);
		data->exit_status = i / 256;
	}
	if (pid > 0 && data->pipe_num < data->is_pipe - 1)
		execute_pipe(data, env);
}
