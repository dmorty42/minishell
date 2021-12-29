/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:33:31 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/28 22:51:43 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_declare(t_node *data)
{
	int	i;
	int	j;
	
	i = 0;
	j = 1;
	while (data->env_exp[i])
	{
		ft_putstr_fd(data->declare_exp, j);
		ft_putstr_fd(data->env_exp[i], j);
		write(j, "\n", 1);
		free(data->env_exp[i++]);
	}
	free(data->env_exp);
}
