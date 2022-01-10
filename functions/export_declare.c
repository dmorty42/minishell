/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_declare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:33:31 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/09 19:43:01 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_declare(t_node *data)
{
	// int	i;
	// int	j;
	
	// i = 0;
	// j = 1;
	t_env	*tmp;
	
	// i = 0;
	tmp = data->env_lst;
	while (tmp)
	{
		// ft_putstr_fd(data->declare_exp, j);
		// ft_putstr_fd(data->env_exp[i++], j);
		// write(j, "\n", 1);
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	// free(data->env_exp);
}
