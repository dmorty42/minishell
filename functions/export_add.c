/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:10:34 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/20 03:25:16 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*export_add2(t_node *data, int j, int i, t_env	*tmp)
{
	tmp = ft_lstnew_env();
	tmp->key = ft_substr(data->cmd[i], 0, j);
	tmp->value = 0;
	tmp->flag = 0;
	return (tmp);
}

void	export_add(t_node *data, int j, int i)
{
	t_env	*tmp;
	int		x;

	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->key = ft_substr(data->cmd[i], 0, j);
	tmp->flag = ft_env_size(data->env_lst) + 1;
	tmp->next = NULL;
	j += 1;
	x = j;
	if (data->cmd[i][j])
	{
		while (data->cmd[i][j])
			j++;
		tmp->value = ft_substr(data->cmd[i], x, j - x);
	}
	else
		tmp->value = NULL;
	ft_lstadd_back_env(&data->env_lst, tmp);
}
