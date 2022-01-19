/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:14:15 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/19 20:14:06 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**two_dim_work(char **array, char *str, int *j)
{
	char	**temp;
	int		i;

	temp = (char **)malloc(sizeof(char *) * (*j + 2));
	i = 0;
	if (array)
	{
		while (array[i])
		{
			temp[i] = ft_strdup(array[i]);
			free(array[i]);
			i++;
		}
		free(array);
	}	
	temp[i] = ft_strdup(str);
	temp[i + 1] = NULL;
	free(str);
	*j += 1;
	return (temp);
}

void	again_check_quotes(char *line, int *i)
{
	if (line[*i] == '\'')
	{
		*i += 1;
		while (line[*i] != '\'')
			*i += 1;
	}
	if (line[*i] == '\"')
	{
		*i += 1;
		while (line[*i] != '\"')
			*i += 1;
	}
}

void	check_semicolon(char *line, t_node *data)
{
	int		i;
	int		j;
	int		x;
	char	*temp;

	j = 0;
	i = 0;
	x = 0;
	while (line[i])
	{
		again_check_quotes(line, &i);
		if (line[i] == ';')
		{
			data->cmd_num += 1;
			temp = ft_substr(line, x, i - x);
			data->arg = two_dim_work(data->arg, temp, &j);
			x = i + 1;
		}
		i++;
	}
	if (x < ft_strlen(line))
	{
		temp = ft_substr(line, x, ft_strlen(line) - x);
		data->arg = two_dim_work(data->arg, temp, &j);
	}
}
