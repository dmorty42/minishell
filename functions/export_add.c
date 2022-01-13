/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 20:10:34 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/12 21:24:51 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_add(t_node *data, int j, int i)
{
	t_env	*tmp;
	char	*ctmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (tmp->key[j] == '\0')
		{
			ctmp = ft_substr(data->cmd[i], 0, j);
			if (!ft_strcmp(tmp->key, ctmp))
				break ;
			free(ctmp);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = ft_lstnew_env();
		tmp->key = ft_substr(data->cmd[i], 0, j);
		tmp->value = ft_strdup(data->cmd[i]);
		// temp->vision = 1,
		 ft_lstadd_back_env(&data->env_lst, tmp);
	}
	else
		 free(ctmp);
		// tmp->vision = 1,
}