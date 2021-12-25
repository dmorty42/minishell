/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:49:46 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/25 17:05:48 by bprovolo         ###   ########.fr       */
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
		while (data->redir_num)
		{
			dup2(data->red->fd, data->red->dup_num);
			data->redir_num--;
			data->red = data->red->next;
		}
		if (buildin_1(data))
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
	wait(&i);
}

void	init(t_node *data)
{
	data->cmd = NULL;
	data->cmd_num = 1;
	data->redir_num = 0;
	data->red = NULL;
}

void	red_clear(t_node *data)
{
	t_red	*temp;

	while (data->red)
	{
		temp = data->red->next;
		data->red = NULL;
		data->red = temp;
	}
}

void	cycle_clean(t_node *data)
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
	if (data->redir_num)
		red_clear(data);
	data->redir_num = 0;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_node	*data;
	int		i;

	i = 0;
	argv = NULL;
	data = (t_node *)malloc(sizeof(t_node));
	data->env_lst = parse_env(data, env);
	init(data);
	while (argc)
	{
		line = readline("minishell: ");
		add_history(line);
		data->cmd_num = 1;
		i = 0;
		check_semicolon(line, data);
		while (data->cmd_num > 0)
		{
			data->arg[i] = space_prepare(data->arg[i]);
			parser(data->arg[i], data->env_lst, data);
			execute_cmd(data, env);
			cycle_clean(data);
			i++;
			data->cmd_num--;
		}
	}
}
