/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:49:46 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/18 18:49:16 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_node *data)
{
	data->cmd = NULL;
	data->arg = NULL;
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
	data->is_err = 0;
	data->exit_status = 0;
}

int	is_shell(t_node *data, int *i)
{
	int	pid;
	int	x;

	x = 0;
	if (data->arg[*i][0] != '.')
		return (0);
	signal(SIGINT, SIG_IGN);
	data->cmd = ft_split(data->arg[*i], ' ');
	pid = fork();
	if (pid == 0)
		execve(data->cmd[0], data->cmd, lst_to_array(data));
	waitpid(pid, &x, 0);
	signal(SIGINT, SIG_DFL);
	data->exit_status = x / 256;
	*i += 1;
	return (1);
}

void	lets_rock(t_node *data, char **env, char *line)
{
	int	i;

	add_history(line);
	data->cmd_num = 1;
	i = 0;
	check_syntax(line, data);
	if (data->is_err == 0)
		check_semicolon(line, data);
	while (data->cmd_num > 0 && data->is_err == 0)
	{
		data->arg[i] = space_prepare(data->arg[i]);
		check_pipe(data, i);
		if (is_shell(data, &i))
		{
			free(data->cmd);
			data->cmd = NULL;
			break ;
		}
		parser(data->arg[i], data->env_lst, data);
		if (!data->is_err)
			execute_cmd(data, env);
		cycle_clean(data, 1);
		i++;
		data->cmd_num--;
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
	signal_work();
	while (argc)
	{
		line = NULL;
		line = readline("minishell: ");
		if (line == NULL)
			line = ft_strdup("exit");
		if (line && ft_strlen(line) > 0)
			lets_rock(data, env, line);
		free(line);
		if (data->arg)
			free(data->arg);
	}
}
