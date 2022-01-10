/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:14:15 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/09 16:04:48 by dmorty           ###   ########.fr       */
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
	}	
	temp[i] = ft_strdup(str);
	temp[i + 1] = NULL;
	free(array);
	free(str);
	*j += 1;
	return (temp);
}

void	check_semicolon(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ';')
			data->cmd_num += 1;
	}
	data->arg = ft_split(line, ';');
}
