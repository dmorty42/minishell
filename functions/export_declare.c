/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:33:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/17 19:31:15 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_declare(t_node *data)
{
	int	i; 
	int	j;

	j = 1;
	i = 0;
	while (data->env_exp[i])
	{
		write(j, "declare -x ", 11);
		ft_putstr_fd(data->env_exp[i], j);
		// write(j, &c, 1);
		write(j, "\n", 1);
		free(data->env_exp[i++]);
	}
	free(data->env_exp);
}
