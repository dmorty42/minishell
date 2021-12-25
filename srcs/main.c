/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:49:46 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/24 05:07:11 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_node *data, char **env)
{
	int		i;
	char	*temp;
	int		pid;

	i = -1;
	pid = fork();
	if (pid == 0)
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
		if (isItBuildin(data))
		{
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
	}
	if (pid > 0)
		wait(NULL);
	if (pid > 0 && data->pipe_num < data->is_pipe)
		execute_pipe(data, env);
}

void	init(t_node *data)
{
	data->cmd = NULL;
	data->cmd_num = 1;
	data->her.is_heredoc = 0;
	data->r.r_num = 0;
	data->r.l_num = 0;
	data->r.r_fd = 0;
	data->r.l_fd = 0;
	data->r.x_fd = 0;
	data->r.x_num = 0;
	data->pipe_num = 10;
	data->is_pipe = 0;
}

void	cycle_clean(t_node *data, int flag)
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
	{
		i = -1;
		if (data->temp)
		{
			while (data->temp[++i])
				free(data->temp[i]);
			free(data->temp);
			data->temp = NULL;
		}
		data->pipe_num = 10;
		data->is_pipe = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*data;
	int		i;

	i = 0;
	argv = NULL;
	line = NULL;
	data = (t_node *)malloc(sizeof(t_node));
	data->env_lst = parse_env(data, env);
	init(data);
	while (argc)
	{
		line = readline("minishell: ");
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			data->cmd_num = 1;
			i = 0;
			check_semicolon(line, data);
			while (data->cmd_num > 0)
			{
				data->arg[i] = space_prepare(data->arg[i]);
				check_pipe(data, i);
				parser(data->arg[i], data->env_lst, data);
				execute_cmd(data, env);
				cycle_clean(data, 1);
				i++;
				data->cmd_num--;
			}
		}
	}
}
