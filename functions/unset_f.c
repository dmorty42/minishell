/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:25:18 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/23 22:52:40 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_f(t_node *data)
{
	int		i;
	int		j;
	char	*tmp;
	t_env	*temp;
	t_env	*temp2;

	i = 0;
	// data->ff_exit = 0;
	while (data->cmd[++i])
	{
		if (is_valid_uns(list, i))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(list->full_cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			// data->ff_exit = 1;
			continue ;
		}
		j = 0;
		temp = data->env_lst;
		j = ft_strlen(data->cmd[i]);
		tmp = ft_substr(list->cmd[i], 0, j);
		temp2 = temp, unset_f2(temp, temp2, data, tmp);
		free(tmp);
	}
}