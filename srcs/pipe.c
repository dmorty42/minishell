/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 01:04:17 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/19 20:16:37 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**pipe_split(char *str, t_node *data)
{
	char	**temp;
	int		i;
	int		x;
	int		j;

	temp = (char **)malloc(sizeof(char *) * data->is_pipe + 1);
	i = 0;
	x = 0;
	j = -1;
	while (str[i])
	{
		again_check_quotes(str, &i);
		if (str[i] == '|')
		{
			i++;
			temp[++j] = ft_substr(str, x, i - x - 1);
			x = i;
		}
		i++;
	}
	if (j < data->is_pipe)
		temp[++j] = ft_strdup(str + x);
	temp[++j] = NULL;
	return (temp);
}

void	check_pipe(t_node *data, int i)
{
	int		j;

	j = -1;
	while (data->arg[i][++j])
	{
		again_check_quotes(data->arg[i], &j);
		if (data->arg[i][j] == '|')
			data->is_pipe += 1;
	}
	j = -1;
	if (data->is_pipe)
	{
		data->fd = (int **)malloc(sizeof(int *) * data->is_pipe);
		while (++j < data->is_pipe)
		{
			data->fd[j] = (int *)malloc(sizeof(int) * 2);
			pipe(data->fd[j]);
		}
		data->is_pipe += 1;
		data->temp = pipe_split(data->arg[i], data);
		free(data->arg[i]);
		data->arg[i] = ft_strdup(data->temp[0]);
		data->pipe_num = 0;
	}
}

void	execute_pipe(t_node *data, char **env)
{
	char	*temp;

	cycle_clean(data, 0);
	temp = ft_strdup(data->temp[data->pipe_num + 1]);
	temp = space_prepare(temp);
	parser(temp, data);
	data->pipe_num += 1;
	execute_cmd(data, env);
}

void	pipe_dup(t_node *data)
{
	if (data->pipe_num == 0)
	{
		dup2(data->fd[0][1], 1);
	}
	else if (data->pipe_num < data->is_pipe - 1)
	{
		dup2(data->fd[data->pipe_num - 1][0], 0);
		dup2(data->fd[data->pipe_num][1], 1);
	}
	else if (data->pipe_num == data->is_pipe - 1)
	{
		dup2(data->fd[data->pipe_num - 1][0], 0);
	}
}
