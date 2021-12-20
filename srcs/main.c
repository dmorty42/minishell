/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:49:46 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/20 19:06:37 by bprovolo         ###   ########.fr       */
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
		if (isItBuildin(data))
		{
			while (data->path[++i])
			{
				temp = NULL;
				temp = ft_strjoin(data->path[i], "/");
				temp = ft_strjoin(temp, data->cmd[0]);
				if (access(temp, X_OK) == 0)
					// printf("sosi %s  \n", *env );
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
