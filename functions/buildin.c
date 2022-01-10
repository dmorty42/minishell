/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:26:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/09 19:38:31 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_f(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1000);
	getcwd(buff, 1000);
	if (!buff[0])
		perror("\n Error getcwd \n");
	else
		ft_putstr_fd(buff, 0);
	write(1, "\n", 1);
}

void	echo_f(t_node *data)
{
	int	flag;
	int	tmp;
	int	i;

	tmp = 1;
	flag = 0;
	i = 0;
	if (!(ft_strcmp(data->cmd[i + 1], "-n")))
		flag = 1;
	while (data->cmd[++i])
	{
		ft_putstr_fd(data->cmd[i + flag], tmp);
		if (i + flag + 1 < ft_bigstr_len(data->cmd))
			write(tmp, " ", 1);
	}
	if (flag == 1)
		return ;
	if (!flag)
		write(tmp, "\n", 1);
}

int	buildin_2(t_node *data)
{	
	// if (!l->cmd[0] || !list->cmd[0][0])
	// 	num += 0;
	if (!ft_strcmp(data->cmd[0], "export"))
	{
		if (data->cmd[1])
			export_f(data);
		else
			ft_declare(data);
			// export_f2(data);
	}
		// sleep(1);
	else if (!ft_strcmp(data->cmd[0], "exit"))
		exit_f(data);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		sleep(1);
	else
		return(1);
	// 	if (buildinP2(list, mini, num))
	// 		return (0);
	// mini->lastCMD = 1;
	return (0);
}

int	buildin_1(t_node *data)
{	
	// if (!l->cmd[0] || !list->cmd[0][0])
	// 	num += 0;
	if (!ft_strcmp(data->cmd[0], "pwd"))
		pwd_f();
	else if (!ft_strcmp(data->cmd[0], "echo"))
		echo_f(data);
	else if (!ft_strcmp(data->cmd[0], "cd"))
		cmd_cd(data);
	else if (!ft_strcmp(data->cmd[0], "env"))
		env_f(data);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		unset_f(data);	
	else if(buildin_2(data))
		return(1);
	// 	if (buildinP2(list, mini, num))
	// 		return (0);
	// mini->lastCMD = 1;
	return (0);
}