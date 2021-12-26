/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 23:07:24 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/25 16:52:59 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_f(t_node *data)
{
	t_env	*temp;
	int		tmp;

	tmp = 1;
	// if (list->fPipeIn)
	// 	tmp = mini->dd[num][1];
	// if (list->redirFlag)
	// 	tmp = list->fdOut;
	temp = data->env_lst;
	while (temp)
	{
		if (temp->flag)
		{
			ft_putstr_fd(temp->key, tmp);
			write(tmp, "=", 1);
			ft_putstr_fd(temp->value, tmp);
			write(tmp, "\n", 1);
		}
		temp = temp->next;
	}
	// data->ff_exit = 0;
}
