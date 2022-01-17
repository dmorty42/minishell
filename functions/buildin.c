/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:26:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/17 19:33:05 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_pwd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
}

void	pwd_f(t_node *data)
{
	char	*buff;
	int		fd_out;

	fd_out = 1;
	if (data->r.r_num || data->r.x_num)
		fd_out = data->r.r_fd;
	if (data->is_pipe)
		fd_out = data->fd[data->pipe_num][1];
	buff = malloc(sizeof(char) * 1000);
	getcwd(buff, 1000);
	if (!buff[0])
		perror("\n Error getcwd");
	else
	{
		ft_putstr_fd(buff, fd_out);
		write(fd_out, "\n", 1);
	}
	free(buff);
}

void	echo_f(t_node *data)
{
	int	flag;
	int	fd_out;
	int	i;

	fd_out = 1;
	flag = 0;
	i = 1;
	if (data->r.r_num || data->r.x_num)
		fd_out = data->r.r_fd;
	if (data->is_pipe)
		fd_out = data->fd[data->pipe_num][1];
	if (data->cmd[i] == NULL)
	{
		write(fd_out, "\n", 1);
		return ;
	}
	if (!(ft_strcmp(data->cmd[i], "-n")))
	{
		i++;
		flag = 1;
	}
	while (data->cmd[i])
	{
		if (!ft_strcmp(data->cmd[i], "$?"))
			ft_putnbr_fd(data->exit_status, fd_out);
		else
			ft_putstr_fd(data->cmd[i], fd_out);
		if (i + 1 < ft_bigstr_len(data->cmd))
			write(fd_out, " ", 1);
		i++;
	}
	if (flag == 1)
		return ;
	if (!flag)
		write(fd_out, "\n", 1);
}

int	buildin_2(t_node *data)
{	
	if (!ft_strcmp(data->cmd[0], "export"))
	{
		if (data->cmd[1])
			export_f(data);
		else
			export_f2(data);
	}
	else if (!ft_strcmp(data->cmd[0], "exit"))
		exit_f(data);
	else
		return (1);
	return (0);
}

int	buildin_1(t_node *data)
{	
	if (!ft_strcmp(data->cmd[0], "pwd"))
		pwd_f(data);
	else if (!ft_strcmp(data->cmd[0], "echo"))
		echo_f(data);
	else if (!ft_strcmp(data->cmd[0], "cd"))
		cmd_cd(data);
	else if (!ft_strcmp(data->cmd[0], "env"))
		env_f(data);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		unset_f(data);
	else if (buildin_2(data))
		return (1);
	return (0);
}
