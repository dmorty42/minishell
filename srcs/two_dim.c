/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_dim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:14:15 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/18 18:18:57 by bprovolo         ###   ########.fr       */
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
			i++;
		}
	}	
	temp[i] = ft_strdup(str);
	temp[i + 1] = NULL;
	free(array);
	*j += 1;
	return (temp);
}

void	check_semicolon(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == ';')
			data->cmd_num += 1;
	data->arg = ft_split(line, ';');
}
